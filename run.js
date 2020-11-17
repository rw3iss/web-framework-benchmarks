const abResult = require('ab-result');
var exec = require('child_process').exec;


function execute(command, callback) {
    //console.log("executing: " + command);
    exec(command, function(error, stdout, stderr) { 
        callback(stdout); 
    });
};

const C = 50;
const N = 10000;
const URL = "http://localhost:8080/json";
const NUM_TESTS = 10;
const TEST_COMMAND = `ab -k -l -c ${C} -n ${N} ${URL}`;

// Drogon:
//const AB_TEST_COMMAND = "ab -k -l -c 250 -n 10000 ${URL}";
const DELAY_BETWEEN_TESTS = 1000;

let RESULTS = {};

async function run() {
    console.log("\nStarting " + NUM_TESTS + " tests: \n" + TEST_COMMAND + "\n");

    function repeat(index, total) {
        if (index <= total) {
            console.log("Running test sample # " + index + " ...");
            execute(TEST_COMMAND, (output) => {
                    let data = saveResult(parseResult(output));
                    repeat(++index, NUM_TESTS);
            });
        } else {
            averageResults();
        }
    }

    repeat(1, NUM_TESTS);
}

run();


//////////////////////////////////////////////

function parseResult(output) {
    //console.log("parseResults:", output);
    return abResult(output);
}

function saveResult(data) {
    //console.log("saveResult:", data);
    let d = RESULTS[data.document.path];
    if (!d) {
        d = RESULTS[data.document.path] = [];
    }

    let r = {
        test: data.test,
        time: data.time
    };

    d.push(r);
    return r;
}

function averageResults() {
    Object.keys(RESULTS).forEach((key, i) => {
        let results = RESULTS[key];
        let numTests = results.length;
        let total = { timeTaken: 0, rps: 0, tps: 0, rate: 0 };
        
        results.forEach(r => {
            total.timeTaken += r.test.timeTaken;
            total.rps += r.test.requestsPerSecond;
            total.tps += r.test.timePerRequest;
            total.rate += r.test.transferRate;
        });

        let average = {
            timeTaken: parseFloat((total.timeTaken / numTests).toFixed(2)),
            rps: parseFloat((total.rps / numTests).toFixed(2)),
            tps: parseFloat((total.tps / numTests).toFixed(2)),
            rate: parseFloat((total.rate / numTests).toFixed(2))
        }

        console.log(key, "\nAverage for " + NUM_TESTS + " tests:\n", average);
    });
}
