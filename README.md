# Digital Octave

A minimal Electron application with a Node.js C++ addon

The web page that runs in the renderer process in Electron is built with React and the source code files are contained in `/renderer/`.

The Node.js C++ addon **simple-pitch** in this project generates the waveform for each tone and is implemented with N-API. It uses the cross-platform library PortAudio to output signals.

## TL;DR

To quick experience the app, you can [download the installation package](https://github.com/macaronesia/digital-octave/releases) for your operating system.

## Building

1. Install compiler tools for building Node.js C++ addons:

    Please follow [these instructions](https://github.com/nodejs/node-gyp#installation)

2. Bundle the React app source code into `/app/`:
    ```bash
    $ cd renderer
    $ yarn
    $ yarn build
    ``` 

3. Build the C++ addon and bundle the code that runs in the main process:
    ```bash
    $ yarn
    $ yarn build
    ``` 

4. Start the app:
    ```bash
    $ yarn start
    ``` 

5. (Optional) Package apps for the local platform:
    ```bash
    $ yarn package
    ``` 