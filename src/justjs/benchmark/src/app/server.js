import JustWebApplication from '../lib/application';
import Router from './router';
const { log } = require('../lib/utils/log');

// Todo: move
const config = { 
    ADDRESS: '127.0.0.1', 
    PORT: 8080,
    SERVER_NAME: 'my-server', 
    MAXHEADERS: 4096, 
    BUFFER_SIZE: 65536, 
    MONITOR: false,
    NO_DELAY: true,
    KEEP_ALIVE: true,
    REUSE_PORT: true,
    REUSE_ADDRESS: true
};

let app = new JustWebApplication(config);

app.use(Router);

app.start();