// Calculate the avergage number of the array

function average(arr) {
    let sum = 0;
    console.log("The average of ")
    arr.forEach(function addNumbers(item) {
        console.log(item);
        sum += item;
    });
    let avg = sum / arr.length;
    console.log("is: " + avg);
    console.log("");
}


average([0]);
average([1, 2, 3]);
average([1, 2, 3, 4]);
average([1, 4, 4, 4, 1]);
average([-12, -13, 512, 1337]);

