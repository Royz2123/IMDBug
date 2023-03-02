# IMDBug Extension
This subsection is in charge of the VSCode extension that
contacts the model's API.

This extension has been tested on VSCode `>=1.72` so make sure
that you're running the right version. 

## Running the extension

In order to run the extension, choose the version that 
you desire under `extension\versions`, copy it into the 
directory containing you source code, open the directory 
in VSCode, right-click the extension and click 
`install this .vsix` or something similar.

Now click `ctrl-shift-p` and search for `imdbug: Activate`
in order to run the extension. The extension should run 
on every file open, file save, and refresh in the top 
right corner menu. 

## Modifying the extension 

Open `extension\imdbug` in VSCode. In order to modify the
extension you need to download NodeJS version `14` or
higher and then open up the VSCode terminal and run:

```
npm install @vscode/vsce -g
npm install ts
npm run compile
```

Then just go to `Run -> Start Debugging` (Make sure that 
you're running the plugin with `VSCode extension development`). 
This will open up a new VSCode window with the extension running. 
Now you can use it as described in the previous section. 

In order to bundle the plugin, just run: 

```
vsce package
```

and answer yes to all of the questions. This wil create a
`.vsix` plugin file that can be used as before. 

You're all set!

### Thanks

A special thanks to Daniel Goltz for creating this plugin, 
and Ido Machlev for upgrading it!
