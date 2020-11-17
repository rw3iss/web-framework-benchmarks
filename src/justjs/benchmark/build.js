function processDefineRules(contents) {
    // todo: parse all contents, storing #define logic... and replace or removing content with #defines...
}

let definePlugin = {
    name: 'define',
    setup(build) {
        let fs = require('fs');

        build.onLoad({ filter: /\.(t|js)x?$/ }, async (args) => {
            let text = await fs.promises.readFile(args.path, 'utf8')
            return {
                contents: text,
                loader: 'js',
            }
        })

        build.onLoad({ filter: /\.json$/ }, async (args) => {
            let text = await fs.promises.readFile(args.path, 'utf8')
            return {
                contents: JSON.stringify(text.split(/\s+/)),
                loader: 'json',
            }
        })
    }
};

require('esbuild').build({
    entryPoints: ['src/server.js'],
    bundle: true,
    outfile: 'build/server.js',
    plugins: [definePlugin],
    platform: 'node',
    external: ['just']
}).catch(() => process.exit(1))