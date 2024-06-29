#include <iostream>
#include <string>

using namespace std;

class InvalidExamDurationException : public exception {
private:
    string message;
    
public:
    InvalidExamDurationException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class Exam {
protected:
    int examID;
    string subject;
    int duration;

public:
    Exam(int id, const string& subj, int dur) : examID(id), subject(subj) {
        if (dur <= 0) {
            throw InvalidExamDurationException("Exam duration must be positive.");
        }
        duration = dur;
    }
    virtual ~Exam() = default;
    virtual void gradeExam() = 0;
    int getExamID() const { return examID; }
    string getSubject() const { return subject; }
    int getDuration() const { return duration; }
};

class MultipleChoiceExam : public Exam {
private:
    int correctAnswers;

public:
    MultipleChoiceExam(int id, const string& subj, int dur) : Exam(id, subj, dur), correctAnswers(0) {}

    void setCorrectAnswers() {    
		cout<<"mc.exam duration:1hrs"<<"\n\ "<<duration;
	    	cout<<"mc.exam duration:1hrs"<<"\n\ "<<duration;
		cout<<"examid:";
    	cin>>examID;
    	
    	int correct;
    	cout<<"your score=";
    	cin>>correct;
        if (correct >= 0 && correct <= 5) {
            correctAnswers = correct;
        } else {
            cout << "Invalid number of correct answers. Must be between 0 and 5.\n";
        }
    }

    void gradeExam() override {
    	 
        cout << "Multiple Choice Exam (ID: " << getExamID() << ") graded.\n";
       
        if (correctAnswers == 1) {
            
            cout << "Score: 20%\n";
        } else if (correctAnswers == 2) {
            
            cout << "Score: 40%\n";
        } else if (correctAnswers == 3) {
           
            cout << "Score: 60%\n";
        } else if (correctAnswers == 4) {
            
            cout << "Score: 80%\n";
        } else if (correctAnswers == 5) {
        
            cout << "Score: 100%\n";
        } else {
           
            cout << "Score: 0%\n";
            cout << "Result: Fail\n";
        }
    }
};

class EssayExam : public Exam {
private:
    string topic;
    string studentAnswer;

public:
    EssayExam(int id, const string& subj, int dur, const string& t)
        : Exam(id, subj, dur), topic(t) {}

    void setStudentAnswer(const string& answer) {
        studentAnswer = answer;
    }

    void gradeExam() override {
    	cout<<"essay duration:2hrs"<<"\n"<<duration;	
		cout<<"examid:";
    	cin>>examID;
    	
    	
       cout << "Essay Exam (ID: " << getExamID() << ") needs grading.\n";
        cout << "Topic: " << topic << "\n";
        cout << "Student Answer: " << studentAnswer << "\n";
        cout << "Enter score (0-100): ";
        int score;
        cin >> score;

        if (score < 0 || score > 100) {
            cout << "Invalid score. Score must be between 0 and 100.\n";
            return;
        }

        cout << "Essay Exam graded. Score: " << score << "%\n";
        if (score == 0) {
            cout << "Result: Fail\n";
        }
    }
};  
int main() {void studentdetails();
	
    try {
        MultipleChoiceExam mcExam(1, "General Knowledge", 1);
        EssayExam essayExam(2, "Literature", 2, "c++ programming");

        cout << "Grading Multiple Choice Exam:\n";
        mcExam.setCorrectAnswers();   
        mcExam.gradeExam();

        cout << "\nGrading Essay Exam:\n";
        
        essayExam.gradeExam();

    } catch (const exception& e) {
        cerr << "An unexpected error occurred: " << e.what() << endl;
    }

    return 0;
}
