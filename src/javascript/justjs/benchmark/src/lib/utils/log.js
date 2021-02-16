const { print } = just;

// A helper file to print out string/objects primarily for development.

export function log(...args) {
    args.forEach(v => {
        if (typeof v == 'object') {
            print(JSON.stringify(v));
        } else {
            print(v);
        }
    });
}