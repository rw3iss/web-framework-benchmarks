const { print } = just;
const codes = require('./http_codes.json');

export function getHttpPhrase(status) {
    return _codeDict[status].phrase;
}

// load code dictionary into memory

const _codeDict = {};

function _loadCodes() {
    for (const c of codes) {
        if (c) {
            _codeDict[c.code] = c;
        }
    } 
}

_loadCodes();
