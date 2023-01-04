// Ex01-Main
// Define an object includes the list of students, each student has ID, name, array of subjects. 
// Each subject has name and grade. Grade has default = 0.
// Use console.log, JSON.stringify to print the list to console.
var students = [{
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
            grade: 8.5
        },
        {
            name: "Graph Theory",
            grade: 7
        },
        {
            name: "Environment",
            grade: 10
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
            grade: 10
        },
        {
            name: "Graph Theory",
            grade: 10
        },
        {
            name: "Environment",
            grade: 10
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
            grade: 10
        },
        {
            name: "Graph Theory",
            grade: 10
        },
        {
            name: "Environment",
            grade: 10
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
            grade: 10
        },
        {
            name: "Graph Theory",
            grade: 10
        },
        {
            name: "Environment",
            grade: 10
        }
    ]
}
];

console.log(JSON.stringify(students));