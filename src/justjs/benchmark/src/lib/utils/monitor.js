const { print, setInterval, memoryUsage, cpuUsage } = just;

// Just prints out status every second
export function monitor() {
    const last = { user: 0, system: 0 };
    const bw = 1000 * 1000 * 1000;

    setInterval(() => {
        const { rss } = memoryUsage();
        const { user, system } = cpuUsage();
        const upc = ((user - last.user) / 1000000).toFixed(2);
        const spc = ((system - last.system) / 1000000).toFixed(2);
        const { conn, rps, wps } = stats;

        print(`rps ${qps} mem ${rss} conn ${conn} cpu ${upc} / ${spc} Gbps  r ${((rps * 8) / bw).toFixed(2)} w ${((wps * 8) / bw).toFixed(2)}`);

        last.user = user;
        last.system = system;
        stats.rps = stats.wps = qps = 0;
    }, 1000);
};
