let slowRandom = require('./22850034_Ex04-SlowRandom');

let slowController = {};
slowController.generate = async (students) => {
    await Promise.all(students.map(async (student) => {
        await Promise.all(student.subjects.map(async (subject) => {
            subject.grade = await slowRandom(0, 10);
        }));
    }));
}

slowController.average = async (students) => {
    await Promise.all(students.map(async (student) => {
        let sum = 0;
        await Promise.all(student.subjects.map(async (subject) => {
            sum += subject.grade;
        }));
        student.average = sum / student.subjects.length;
    }));
}

slowController.normalize = async (students) => {
    await Promise.all(students.map(async (student) => {
        student.average = student.average.toFixed(2);
        student.subjects.map(async (subject) => {
            subject.grade = subject.grade.toFixed(2);
        });
    }));
}

module.exports = slowController;