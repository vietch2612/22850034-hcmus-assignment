// Variables & Data types
var age = 18;
var name = "Jane";
var name = { first: "Jane", last: "Doe" };
var truth = false;
var sheets = ["HTML", "CSS", "JS"]
var a; typeof a;
var a = null;

// If-else
if ((age >= 14) && (age < 19)) {
    status = "Eligible."
} else {
    status = "Not Eligible."
}
console.log(status);

// Switch-Cases
switch (new Date().getDay()) {
    case 6:
        text = "Saturday";
        break;
    case 0:
        text = "Sunday";
        break;
    default:
        text = "Whatever";
}
console.log(text);

// Loop (For)
var sum = 0;
var a = "This is my first JS exercise."
for (var i = 0; i < a.length; i++) {
    sum += a[i];
}
console.log(sum);

// Loop (While)
var i = 1;
while (i < 200) {
    i *= 2;
    console.log(i + ", ")
}

// Loop (Do-While)
var j = 1;
do {
    j *= 2;
    console.log(j, ", ");
} while (j < 100)

// function
function addNumbers(a, b) {
    return a + b;
}
x = addNumbers(1, 2);
console.log(x);

// Object
var student = {
    firstName: "Jane",
    lastName: "Doe",
    age: 18,
    height: 170,
    fullName: function () {
        return this.firstName + " " + this.lastName;
    }
}
student.age = 19;
student[age]++;
name = student.fullName();

// sort array
var points = [40, 100, 1, 5, 25, 10];
points.sort(function (a, b) { return a - b });
console.log(points);
