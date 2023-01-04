// Sort the array of students by their age, in ascending order.
let students = [{
    firstName: "Viet",
    lastName: "Cao",
    age: 31,
    height: 165,
    fullName: function () {
        return this.firstName + " " + this.lastName;
    }
}, {
    firstName: "Tam",
    lastName: "Doan",
    age: 26,
    height: 160,
    fullName: function () {
        return this.firstName + " " + this.lastName;
    }
}, {
    firstName: "Khang",
    lastName: "Cao",
    age: 19,
    height: 90,
    fullName: function () {
        return this.firstName + " " + this.lastName;
    }
}, {
    firstName: "Tuan",
    lastName: "Vu",
    age: 27,
    height: 190,
    fullName: function () {
        return this.firstName + " " + this.lastName;
    }
}
];

students.sort(function (a, b) { return a.age - b.age });
console.log(students);