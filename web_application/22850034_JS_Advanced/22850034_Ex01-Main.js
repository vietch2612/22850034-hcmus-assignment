// Ex01-Main
// Define an object includes the list of students, each student has ID, name, array of subjects. 
// Each subject has name and grade, default grade = 0
// Use console.log, JSON.stringify to print the list to console.

let controller = require('./22850034_Ex03-StudentController');
let slowController = require('./22850034_Ex05-SlowStudentController');

let students = [{
    firstName: "Viet",
    lastName: "Cao",
    id: 22850034,
    subjects: [
        {
            name: "Web Application",
            grade: 0
        },
        {
            name: "Software Testing",
            grade: 0
        },
        {
            name: "Predicate Logic",
            grade: 0
        },
        {
            name: "Graph Theory",
            grade: 0
        },
        {
            name: "Environment",
            grade: 0
        }
    ]
}, {
    firstName: "Tam",
    lastName: "Doan",
    id: 100000031,
    subjects: [
        {
            name: "Web Application",
            grade: 0
        },
        {
            name: "Software Testing",
            grade: 0
        },
        {
            name: "Predicate Logic",
            grade: 0
        },
        {
            name: "Graph Theory",
            grade: 0
        },
        {
            name: "Environment",
            grade: 0
        }
    ]
}, {
    firstName: "Khang",
    lastName: "Cao",
    id: 100000002,
    subjects: [
        {
            name: "Web Application",
            grade: 0
        },
        {
            name: "Software Testing",
            grade: 0
        },
        {
            name: "Predicate Logic",
            grade: 0
        },
        {
            name: "Graph Theory",
            grade: 0
        },
        {
            name: "Environment",
            grade: 0
        }
    ]
}, {
    firstName: "Tuan",
    lastName: "Vu",
    id: 100000003,
    subjects: [
        {
            name: "Web Application",
            grade: 0
        },
        {
            name: "Software Testing",
            grade: 0
        },
        {
            name: "Predicate Logic",
            grade: 0
        },
        {
            name: "Graph Theory",
            grade: 0
        },
        {
            name: "Environment",
            grade: 0
        }
    ]
}
];

// Create a copy of students
let slowStudents = students;

// Exercise 01
console.log(JSON.stringify(students, undefined, 2));

// Exercise 02
controller.generate(students);
controller.average(students);
controller.normalize(students);
console.log(JSON.stringify(students, undefined, 2));

// Exercise 03
slowController.generate(slowStudents).then(() => {
    slowController.average(slowStudents).then(() =>
        slowController.normalize(slowStudents)).then(() =>
            console.log(JSON.stringify(slowStudents, undefined, 2)));
});
