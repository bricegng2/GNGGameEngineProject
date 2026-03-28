
## Proof of Concept
#### Start by Rendering any Texture into an ImGui window

Can we draw a texture using ImGui?

```c++
    if( ImGui::Begin("Test view") )
    {
        ImTextureID texID = fw::imguiTexture( m_pResources->Get<fw::Texture>("MegaMan")->GetHandle() );
        ImGui::Image( texID, ImVec2(32, 32), vec2(0,0), vec2(1,1) );
    }
    ImGui::End();
```

## Terms

#### View

BGFX works with views. Each view will be processed in order, regardless of what order you call draw. Each view can render into 1 buffer, either the back buffer or a framebuffer.

#### Framebuffer 

A framebuffer is an object that hold 1 or more textures, if it holds just a color texture, only color values will be written to it. If it holds a color texture and a depth texture (holds floats with values from 0 to 1), it will write and test against written depth values when rendering into the color buffer.

## ImGui Dockspace

To start to make our Game feel more like an editor, we need to be able to dock windows to the outside frame of view.

To do this, we'll create a full screen window with no border and titlebar and set it up for docking.

```c++
void Game::Editor_CreateMainFrame()
{
    // Setup a main window with no frame and a dockspace that covers the entire viewport.
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos( viewport->WorkPos );
    ImGui::SetNextWindowSize( viewport->WorkSize );

    if( ImGui::Begin( "Main Dock", nullptr, flags ) )
    {
        ImGuiID dockspaceID = ImGui::GetID( "My Dockspace" );
        ImGui::DockSpace( dockspaceID );
    }
    ImGui::End();
}
```

## Render into a Texture

#### Define 2 view IDs

We need 2 views, one for our Game and one for the main render, which in the end is really only ImGui. ImGui will display our texture as a control. We're already doing this, but rather than hard-code the 0 and 1, we'll use an enum.

```c++
enum EditorViews
{
    EditorView_Game,
    EditorView_ImGui,
};
```

Fix any code that uses a ViewID. Define this enum so any code needing to set a viewID can or adjust code to have a settable viewID.

#### Create a Texture for the Game to Render into

The game will ultimately render into a texture of our choosing instead of rendering into the backbuffer (which is essentially just a texture). We need both a color buffer and a depth buffer.

```c++
    // This is a hard-coded 4096x4096 texture, bigger than we should need.
    // In a complete engine this texture would need to be destroyed
    //     and regenerated if we needed a bigger version.
    m_Game_FBOTexture = bgfx::createTexture2D( 4096, 4096, false, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_RT );
	m_Game_FBODepth = bgfx::createTexture2D( 4096, 4096, false, 1, bgfx::TextureFormat::D32, BGFX_TEXTURE_RT );
```

#### Create a Framebuffer Object

A framebuffer object is needed to redirect draw calls into the texture of choice.

```c++
	// Create the framebuffer with the texture and depth buffers.
    bgfx::TextureHandle gameTextures[] = { m_Game_FBOTexture, m_Game_FBODepth };
    m_Game_FBO = bgfx::createFrameBuffer( 1, gameTextures, true );
```

#### Set the Game view to draw to the Framebuffer

```c++
    bgfx::setViewFrameBuffer( EditorView_Game, m_Game_FBO );
```

#### Set the Clear properties for both Views

```c++
    bgfx::setViewClear( EditorView_Game, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000030ff, 1.0f, 0 );

    bgfx::setViewClear( EditorView_ImGui, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x001000ff, 1.0f, 0 );
```

#### Set a few vars when the window resizes

I'm not sure why we need to reset the framebuffer, but if we don't the texture will stop being updated. Set the view rect for the imgui/backbuffer render to the entire window size.

```c++
	bgfx::setViewFrameBuffer( EditorView_Game, m_Game_FBO );
	bgfx::setViewRect( EditorView_ImGui, 0, 0, width, height );
```

#### Every frame draw a "Game View" ImGui window

A few things:
- Create an ImGui window
	- This is incomplete, it's hard-coded to a 1000x1000 area, we want to resize and set UVs based on the actual imgui window size
- Set the aspect ratio of the camera
- Set the view rect to decide what part of the texture to render to
- Draw an ImGui::Texture
	- We don't have to worry that we haven't drawn our scene yet
	- BGFX will draw all "view 0" commands before it draws "view 1" commands

```c++
    if( ImGui::Begin("Game view") )
    {
        m_pCamera->SetAspectRatio( 500.0f/500.0f );
        bgfx::setViewRect( EditorView_Game, 0, 0, 500, 500 );
        
        ImTextureID texID = fw::imguiTexture( m_Game_FBOTexture );
        ImGui::Image( texID, ImVec2(500, 500), ImVec2(0,0), ImVec2(1,1) );
    }
    ImGui::End();
```

#### How much to render?

We have a 4096x4096 texture to render into. We're only going to use a portion of it, but how much. This will be determined by the "content size" of the imgui window we want to display our game in.

ImGui has the following helpers to determine the size of the content area of a window:
- ImGui::GetWindowContentRegionMin()
- ImGui::GetWindowContentRegionMax()

The will get the left, right, top, and bottom pixel offsets. Using these numbers we know the exact size of the viewport.

Ultimately, if the content area is 400x200 pixels large:
- you want your viewport to be 400x200
- you want your imgui::image call to be 400x200
- you want your uv's to show an area of the texture that is 400/4096 x 200/4096
