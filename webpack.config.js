const path = require('path');
const CopyWebpackPlugin = require('copy-webpack-plugin');

module.exports = {
  entry: './main/src/main.js',
  output: {
    path: path.resolve(__dirname, 'app'),
    filename: 'main.min.js'
  },
  plugins: [
    new CopyWebpackPlugin([
      {
        from: 'build-assets/package.json',
        to: 'package.json'
      },
      {
        from: 'node_modules/simple-pitch/build/Release/simple-pitch.node',
        to: 'addons/simple-pitch.node'
      },
      {
        from: '{portaudio_x86.dll,portaudio_x64.dll,libportaudio.2.dylib,libportaudio.so.2,libportaudio.so.2.0.0}',
        to: 'addons',
        context: 'node_modules/simple-pitch/build/Release/'
      }
    ])
  ],
  module: {
    rules: [
      {
        test: /\.js$/,
        exclude: /node_modules/,
        use: [
          {
            loader: 'babel-loader',
            options: {
              presets: [['env', {'modules': false}], 'stage-2']
            }
          }
        ]
      },
    ]
  },
  node: {
    __dirname: false,
    __filename: false
  },
  devtool: 'source-map',
  target: 'electron-main'
};
