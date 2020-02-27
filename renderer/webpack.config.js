const path = require('path');
const webpack = require('webpack');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const MiniCssExtractPlugin = require('mini-css-extract-plugin');

module.exports = {
  entry: [
    './src/index.jsx'
  ],
  output: {
    path: path.resolve(__dirname, '../app'),
    filename: 'assets/js/bundle.[hash:7].js'
  },
  plugins: [
    new webpack.NormalModuleReplacementPlugin(
      /^bindings$/,
      `${__dirname}/bindings.js`
    ),
    new HtmlWebpackPlugin({
      filename: 'index.html',
      template: path.join(__dirname, 'src/index.html')
    }),
    new MiniCssExtractPlugin({
      filename: 'assets/css/all.min.[hash:7].css'
    })
  ],
  module: {
    rules: [
      {
        test: /\.jsx?$/,
        include: [
          path.resolve(__dirname, 'src')
        ],
        use: [
          {
            loader: 'babel-loader',
            options: {
              presets: [['env', {'modules': false}], 'react', 'stage-2']
            }
          }
        ]
      },
      {
        test: /\.css$/,
        include: [
          path.resolve(__dirname, 'src/assets/css')
        ],
        use: [
          {
            loader: MiniCssExtractPlugin.loader
          },
          {
            loader: 'css-loader',
            options: {
              minimize: true
            }
          }
        ]
      }
    ]
  },
  resolve: {
    alias: {
      '@': path.resolve(__dirname, 'src/')
    }
  },
  devtool: 'source-map',
  target: 'electron-renderer'
};
