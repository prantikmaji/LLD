#include <bits/stdc++.h>
using namespace std;

// Forward declaration for Enrollment (used inside Student)
class Enrollment;

// -------------------- LESSON --------------------
class Lesson
{
    int id;
    string title;
    string contentUrl;
    int durationMinutes;

public:
    Lesson(int id, string title, string contentUrl, int durationMinutes)
        : id(id), title(title), contentUrl(contentUrl), durationMinutes(durationMinutes) {}
};

// -------------------- MODULE --------------------
class Module
{
    int id;
    string title;
    vector<Lesson> lessons;

public:
    Module(int id, string title) : id(id), title(title) {}

    void addLesson(const Lesson &ls)
    {
        lessons.push_back(ls);
    }

    vector<Lesson> getLessons()
    {
        return lessons;
    }
};

// -------------------- COURSE --------------------
class Course
{
    int id;
    string title;
    string description;
    vector<Module> modules;

public:
    Course(int id, string title, string description)
        : id(id), title(title), description(description) {}

    void addModule(const Module &ml)
    {
        modules.push_back(ml);
    }

    vector<Module> getModules()
    {
        return modules;
    }
};

// -------------------- USER --------------------
class User
{
protected:
    int id;
    string name;
    string email;

public:
    User(int id, string name, string email)
        : id(id), name(name), email(email) {}

    int getId() { return id; }
    string getName() { return name; }
    string getEmail() { return email; }

    bool login(string password) { return true; }
};

// -------------------- ENROLLMENT --------------------
class Enrollment
{
    int id;
    string enrollmentDate;
    string status;
    float progressPercent;

public:
    Enrollment(int id, string date)
        : id(id), enrollmentDate(date), status("ACTIVE"), progressPercent(0.0f) {}

    void markLessonCompleted()
    {
        progressPercent += 10.0f;
        if (progressPercent > 100)
            progressPercent = 100;
    }

    float getProgress() { return progressPercent; }
};

// -------------------- STUDENT --------------------
class Student : public User
{
    vector<Enrollment> enrollments;

public:
    Student(int id, string name, string email)
        : User(id, name, email) {}

    void addEnrollment(const Enrollment &e)
    {
        enrollments.push_back(e);
    }

    vector<Enrollment> getEnrollments()
    {
        return enrollments;
    }
};

// -------------------- INSTRUCTOR --------------------
class Instructor : public User
{
    vector<Course> courses;

public:
    Instructor(int id, string name, string email)
        : User(id, name, email) {}

    void addCourse(const Course &c)
    {
        courses.push_back(c);
    }

    vector<Course> getCourses()
    {
        return courses;
    }
};

int main()
{
    // ---------------- CREATE LESSONS ----------------
    Lesson l1(1, "Intro to C++", "url1", 10);
    Lesson l2(2, "Variables & Types", "url2", 15);
    Lesson l3(3, "Loops", "url3", 20);

    // ---------------- CREATE MODULE ----------------
    Module m1(1, "Basics of C++");
    m1.addLesson(l1);
    m1.addLesson(l2);
    m1.addLesson(l3);

    // ---------------- CREATE COURSE ----------------
    Course c1(101, "C++ Masterclass", "Learn C++ from beginner to advanced");
    c1.addModule(m1);

    // ---------------- CREATE INSTRUCTOR ----------------
    Instructor inst(10, "John Doe", "john@course.com");
    inst.addCourse(c1);

    // ---------------- CREATE STUDENT ----------------
    Student st(20, "Ayan", "ayan@mail.com");

    // ---------------- ENROLL STUDENT ----------------
    Enrollment e1(1001, "2025-01-01");
    st.addEnrollment(e1);

    // ---------------- MARK LESSON COMPLETED ----------------
    cout << "Progress before completion: "
         << st.getEnrollments()[0].getProgress() << "%\n";

    // Mark completion 3 times
    st.getEnrollments()[0].markLessonCompleted();
    st.getEnrollments()[0].markLessonCompleted();
    st.getEnrollments()[0].markLessonCompleted();

    cout << "Progress after completion: "
         << st.getEnrollments()[0].getProgress() << "%\n";

    // ---------------- INSTRUCTOR COURSES ----------------
    cout << "\nInstructor: " << inst.getName()
         << " teaches " << inst.getCourses().size() << " course(s)\n";

    return 0;
}
