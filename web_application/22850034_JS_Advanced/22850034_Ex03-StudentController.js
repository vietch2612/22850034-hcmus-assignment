let random = require('./22850034_Ex02-Random');

let controller = {};
controller.generate = (students) => {
    students.map((student) => {
        student.subjects.map((subject) => {
            subject.grade = random(0, 10);
        });
    });
}

controller.average = (students) => {
    students.map((student) => {
        let sum = 0;
        student.subjects.map((subject) => {
            sum += subject.grade;
        });
        student.average = sum / student.subjects.length;
    });
}

controller.normalize = (students) => {
    students.map((student) => {
        student.average = student.average.toFixed(2);
        student.subjects.map((subject) => {
            subject.grade = subject.grade.toFixed(2);
        });
    });
}

module.exports = controller;