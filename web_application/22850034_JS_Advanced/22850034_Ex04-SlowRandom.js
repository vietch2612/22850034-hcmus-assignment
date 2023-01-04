const sleep = async ms => new Promise(r => setTimeout(r, ms));

const slowRandom = async (min, max) => {
    await sleep(1_000);
    return min + Math.random() * (max - min);
};

module.exports = slowRandom;
