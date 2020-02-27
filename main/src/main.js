import path from 'path';
import url from 'url';

import { app, BrowserWindow } from 'electron';

let win;

function createWindow () {
  win = new BrowserWindow({
    webPreferences: {
      nodeIntegration: true
    }
  });
  win.loadURL(
    url.format({
      pathname: path.join(__dirname, './index.html'),
      protocol: 'file:',
      slashes: true
    })
  );
  // win.webContents.openDevTools();
  win.on('closed', () => {
    win = null
  });
}

app.on('ready', createWindow);

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

app.on('activate', () => {
  if (win === null) {
    createWindow();
  }
});

app.on('browser-window-created', function(e, window) {
  window.setMenu(null);
});
