
## Building Custom Plugins

- nvm (Node Version Manager)
	- https://github.com/nvm-sh/nvm
	- curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.7/install.sh | bash
- node.js
	- nvm install node
- everything else
	- https://docs.obsidian.md/Plugins/Getting+started/Build+a+plugin
	- Clone repo
	- npm install
	- npm run dev
- Updating code:
	- **Command palette**, select **Reload app without saving**

## Debug
- `ctrl-alt-i`
- in console: `app.plugins.plugins["[Plugin ID]"].constructor`


`app.plugins.plugins[reference-map-custom].constructor`