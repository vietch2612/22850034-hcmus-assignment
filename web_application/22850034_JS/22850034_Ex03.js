// Print the first 30 fibonacci
// 0, 1, 1, 2, 3, 5, 8, ....

function fibonacci(index) {
    if (index == 0) {
        return 0;
    } else if (index == 1) {
        return 1;
    } else {
        return fibonacci(index - 2) + fibonacci(index - 1);
    }
}

var i = 0
while (i < 30) {
    console.log('Fibonacci\'s number ' + i + ' is: ' + fibonacci(i));
    i++;
}

