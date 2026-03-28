
## Markdown

# Header 1
## Header 2
### Header 3
#### Header 4
##### Header 5
###### Header 6

- Bullet lists
	- Can be tabbed in

1. Numbered list
	1. sub-number entry
2. Entry two

> Blockquotes
>> Nested blockquotes

This sentence has **bold** words, *italic* words, and ***bolded italics***

~~Strikethrough~~
**Bold**
*Italics*
***Bold Italics***

---

`Code lines`

```c++
Code Blocks
```

Wiki link:
```
[Links](Links)
```

Markdown link:
```
[Links](Links.md)
```

Images: the width of 50 is Obsidian specific, there are different ways to deal with it but none seems completely compatible.

Wiki image link
```
![50](Mario)
```

Markdown image link ![Mario|50](Mario.png)

> [!info] Callout Block
> 
> This is a callout block
> ```
> It can hold a code block
> ```
> 
> Regular text, with **bold**, etc
> > [!info]  Nested callout
> > And nested Callouts
> 
> It can even hold a collapsed callout 
> 
> > [!info]- Collapsible Callout
> > This is a collapsible callout block.
> > ![Mario|50](Mario.png)
> 
> Beware of spacing when making these.

> [!info]- Another Collapsible Test
> This is another collapsible callout block.

Note: Image Sizes and Collapsible Callouts don't seem to work on GitHub

## Tables

| Tables   |      Are      |  Cool |
|----------|:-------------:|------:|
| col 1 is |  left-aligned | $1600 |
| col 2 is |    centered   |   $12 |
| col 3 is | right-aligned |    $1 |
