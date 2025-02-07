// UMBC - CMSC 341 - Spring 2025 - Tester file
#include "course.h"
class Tester{
    public:
    bool testStudentAveErrorCase();
    /******************************************
    * Test function declarations go here! *
    ******************************************/
    bool testCourseDConstructorDef();//default course constructor
    bool testCourseOConstructorDef();//overloaded course constructor
    bool testInsertSectionValue();//the pass by value insert section
    bool testInsertSectionRef(); //pass by ref insert section
    bool testCourseAvg();//Course Avg
};
int main(){
    bool result = false;
    Tester tester;
    cout<<endl;
    //student Avg
    cout<<"Testing the Student Avg function:"<<endl;
    result = tester.testStudentAveErrorCase();
    if (result == true){cout<<"Result of testing studentAverage: true"<<endl;}
    else{cout<<"Result of testing studentAverage: false"<<endl;}
    cout<<endl;

    //course default constructor test
    cout<<"Testing Course default constructor:"<<endl;
    result = tester.testCourseDConstructorDef();
    if (result == true){cout<<"Result of testing Course default constructor: true"<<endl;}
    else{cout<<"Result of testing Course default constructor: false"<<endl;}
    cout<<endl;

    //course overlaoded constructor test
    cout<<"Testing Course overloaded constructor:"<<endl;
    result = tester.testCourseOConstructorDef();
    if (result == true){cout<<"Result of testing Course overloaded constructor: true"<<endl;}
    else{cout<<"Result of testing Course overloaded constructor: false"<<endl;}
    cout<<endl;

    //insertSec val
    cout<<"Testing the InsertSection[value] function:"<<endl;
    result = tester.testInsertSectionValue();
    if (result == true){cout<<"Result of testing InsertSection[value]: true"<<endl;}
    else{cout<<"Result of testing InsertSection[value]: false"<<endl;}
    cout<<endl;

    //insertSec ref
    cout<<"Testing the InsertSection[ref] function:"<<endl;
    result = tester.testInsertSectionRef();
    if (result == true){cout<<"Result of testing InsertSection[ref]: true"<<endl;}
    else{cout<<"Result of testing InsertSection[ref]: false"<<endl;}
    cout<<endl;

    //CourseAvg func
    cout<<"Testing the Course Avg function:"<<endl;
    result = tester.testCourseAvg();
    if (result == true){cout<<"Result of testing courseAverage: true"<<endl;}
    else{cout<<"Result of testing courseAverage: false"<<endl;}
    cout<<endl;
    return 0;
}

//Student Avg
bool Tester::testStudentAveErrorCase(){
    bool result = true;
    // create an object with 1 student and 10 grading items
    Section testObject(1000,"John Smith",10,1);
    testObject.simulateData();
    double average = testObject.studentAverage(1);// out of range index
    if (average == 0.0) // expected output
        result = true;
    else
        result = false;
    return result;
}

//Default Course constructor
bool Tester::testCourseDConstructorDef(){
    bool result = true;
    Course aCourse = Course();
    //Checks the default value of maxNumSections
    if (aCourse.m_maxNumSections <= 0){
        result = false;
    }
    else{
        result = true;
    }
    if(result){
        //Checks default value of numSections
        if (aCourse.m_numSections < 0 || aCourse.m_numSections>0){
            result = false;
        }
        else{
            result = true;
        }
    }
    else{
        return result;
    }
    if(result){
        //checks if m_course is empty
        if(aCourse.m_course==nullptr){
            result = false;
        }
        else{
            result = true;
        }
    }
    else{
        return result;
    }
    return result;
}

//Overlaoded Course Constructor
bool Tester::testCourseOConstructorDef(){
    bool result = true;
    //valid size
    Course aCourse(3);
    //size check
    if (aCourse.m_maxNumSections <= 0){
        result = false;
    }
    else{
        result = true;
    }

    //if the result is true continue
    if (result){
        //invalid size
        Course bCourse(0);
        //size check
        if (bCourse.m_maxNumSections <= 0){
            result = true;
        }
        else{
            result = false;
        }
    }
    else{
        return result;
    }
    if(result){
        //checks if m_course is empty
        if(aCourse.m_course==nullptr){
            result = false;
        }
        else{
            result = true;
        }
    }
    else{
        return result;
    }
    return result;
}

//Insert Section Pass by Value
bool Tester::testInsertSectionValue(){
    bool result = true;
    Course aCourse(3);
    //if the result is true continue
    if (result){
        //fresh insert
        int ID = 1000;
        string instructor = "John Smith";
        int items = 10;
        int students = 1;
        aCourse.insertSection(ID,instructor,items,students);//running the function the first time
        aCourse.insertSection(ID,instructor,items,students);//making sure it checks for duplicate IDs
        Section *testObject = aCourse.getSection(1000);
        if (testObject != nullptr){
            result = true;
        }
        else{
            result = false;
        }
    }
    else{
        return result;
    }

    //if the result is true continue
    if (result){
        //New insert
        //updates the values
        int ID = 4000;
        string instructor = "John Smith";
        int items = 12;
        int students = 4;
        aCourse.insertSection(ID,instructor,items,students);//inserting the new section
        //setting the object to dump
        Section *testObject = aCourse.getSection(4000);
        if (testObject != nullptr){
            result = true;
        }
        else{
            result = false;
        }
    }
    else{
        return result;
    }

    //if the result is true continue
    if (result){
        //Invalid insert
        Section *testObject = aCourse.getSection(5000);
        if (testObject != nullptr){
            result = false;
        }
        else{
            result = true;
        }
    }
    else{
        return result;
    }

    return result;
}

//Insert Section pass by referednce
bool Tester::testInsertSectionRef(){
    Course aCourse(3);
    bool result = true;
    //making Sections
    Section * aSection = new Section(1000,"John Smith", 8, 8);
    Section * bSection = new Section(1000,"John Smith", 8, 8);
    Section * cSection = new Section(4000,"John Smith", 8, 8);
    Section * dSection = new Section(5000,"John Smith", 8, 8);
    Section * eSection = new Section(2000,"John Smith", 8, 8);
    //Valid insertion
    if(result){
        result = aCourse.insertSection(aSection);
    }
    else{
        return result;
    }
    //duplicate insertion
    if(result){
        if(!aCourse.insertSection(bSection)){
            result = true;
        }
        else{
            result=false;
        }
    }
    else{
        return result;
    }
    //valid next insertion
    if(result){
        result = aCourse.insertSection(cSection);
    }
    else{
        return result;
    }
    //maxing size insertion
    if(result){
        result = aCourse.insertSection(dSection);
    }
    else{
        return result;
    }    
    //out of range insertion
    if(result){
        if(!aCourse.insertSection(eSection)){
            result = true;
        }
    }
    else{
        return result;
    }
    aSection->clear();
    return result;
}

//Course Avg test
bool Tester::testCourseAvg(){
    bool result = true;
    //making the course
    Course aCourse(3);
    //making the sections
    Section * aSection = new Section(1000,"John Smith", 8, 8);
    Section * bSection = new Section(2000,"John Smith", 8, 8);
    Section * cSection = new Section(3000,"John Smith", 8, 8);
    //Adding dummy data
    aSection->simulateData();
    bSection->simulateData();
    cSection->simulateData();
    //inserting the sections into course
    aCourse.insertSection(aSection);
    aCourse.insertSection(bSection);
    aCourse.insertSection(cSection);
    //Running average function
    double avg = aCourse.courseAverage();
    cout<<avg<<endl;
    if(avg>0){
        result = true;
    }
    else{
        result = false;
    }
    return result;
}