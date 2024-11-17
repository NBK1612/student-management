#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <Windows.h>

using namespace std;

class User {
public:
    string username;
    string password;

    User(string name, string pass) : username(name), password(pass) {}

    bool Login(const string& inputUsername, const string& inputPassword) const {
        return (inputUsername == username && inputPassword == password);
    }
};

class Student {
public:
    int id;
    string studentName;
    string dateOfBirth;
    string gender;
    string studentClass;
    vector<pair<string, float> > grades; 

    Student(int studentId, string name, string dob, string studentGender, string sClass)
        : id(studentId), studentName(name), dateOfBirth(dob), gender(studentGender), studentClass(sClass) {}

    void addGrade(const string& subject, double grade) {
        grades.push_back(make_pair(subject, grade));
    }

    double calculateAverageGrade() {
        if (grades.empty()) {
            return 0.0; // Tra ve 0 neu khong co diem nao
        }

        double totalGrade = 0.0;
        for (const auto& grade : grades) {
            totalGrade += grade.second;
        }

        return totalGrade / grades.size();
    }

    string getAcademicPerformance() {
        double avgGrade = calculateAverageGrade();
        if (avgGrade >= 9.0) {
            return "Xuat sac";
        } else if (avgGrade >= 8.0) {
            return "Gioi";
        } else if (avgGrade >= 6.5) {
            return "Kha";
        } else if (avgGrade >= 5.0) {
            return "Trung binh";
        } else {
            return "Yeu";
        }
    }
};


class Professor {
public:
    string professorName;
    string courseTeaching;

    Professor(string name, string course) : professorName(name), courseTeaching(course) {}
};

void pressAnyKey() {
    cout << "\n\nBam phim bat ky de tiep tuc...";
    getch();
    system("cls");
}

void loadStudentsFromFile(vector<Student>& students) {
    ifstream file("sinhvien.txt");
    if (!file) {
        cout << "Khong the mo file sinhvien.txt de doc." << endl;
        return;
    }

    students.clear(); // Xóa danh sách sinh viên hi?n t?i d? c?p nh?t d? li?u m?i

    while (!file.eof()) {
        int id;
        string name, dob, gender, sClass;

        file >> id;
        file.ignore();
        getline(file, name);
        getline(file, dob);
        getline(file, gender);
        getline(file, sClass);

        Student student(id, name, dob, gender, sClass);
        students.push_back(student);
    }

    file.close();
}


void saveStudentsToFile(const vector<Student>& students) {
    ofstream file("sinhvien.txt"); // T?o ho?c m? t?p d? ghi

    if (file.is_open()) {
        for (const Student& student : students) {
        	file << left << setw(10) << student.id << setw(30) << student.studentName << setw(30) << student.dateOfBirth << setw(30) << student.gender << setw(10) << student.studentClass << endl;

            for (const auto& grade : student.grades) {
                file << grade.first << "," << grade.second << "\n";
            }
        }

        file.close(); // Ðóng t?p sau khi ghi xong
        cout << "Luu du lieu sinh vien vao file thanh cong." << endl;
    } else {
        cout << "Khong the mo hoac tao file sinhvien.txt de ghi." << endl;
    }
}

void loadRegisteredUsersFromFile(vector<User>& registeredUsers) {
    ifstream file("registered_users.txt");
    if (file) {
        registeredUsers.clear();
        string username, password;
        while (file >> username >> password) {
            registeredUsers.push_back(User(username, password));
        }
        file.close();
    }
}

void saveRegisteredUsersToFile(const vector<User>& registeredUsers) {
    ofstream file("registered_users.txt");
    if (file) {
        for (const User& user : registeredUsers) {
            file << user.username << " " << user.password << endl;
        }
        file.close();
    }
}

void SET_COLOR(int color)
{
	WORD wColor;
     

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
}

void quanLySinhVienMenu(vector<Student>& students) {
	int nextId = 1;
    while (true) {
        system("cls");
        cout << " ______________________________________ "<< endl;
        cout << "|           Quan Ly Sinh Vien          |"<< endl;
        cout << "|______________________________________|"<< endl;
        cout << "|1. Danh sach sinh vien                |"<< endl;
        cout << "|2. Quan ly diem sinh vien             |"<< endl;
        cout << "|3. Quan ly mon hoc cho sinh vien      |" << endl;
        cout << "|4. Luu du lieu sinh vien vao file     |"<< endl;
        cout << "|0. Tro ve menu chinh                  |"<< endl;
        cout << "|______________________________________|"<< endl;
        cout << "Nhap lua chon cua ban: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
			    while (true) {
			        // Hien thi danh sach sinh viên
			        system("cls");
			        cout << " __________________________________________________________________________________________" << endl;
			        cout << "|                                    Danh Sach Sinh Vien                                   |" << endl;
			        cout << "|__________________________________________________________________________________________|" << endl;
			        cout << left << "|STT|" << setw(10) << "ID" << setw(25) << "|Ho va ten" << setw(25) << "|Ngay sinh" << setw(15) << "|Gioi tinh" << setw(11) << "|Lop" << "|" << endl;
			        cout << "|___|__________|________________________|________________________|______________|__________|" << endl;
			
			        int stt = 1; // So thu tu
			        for (const Student& student : students) {
			            if (student.id != 0) {  // Thêm di?u ki?n d? không hi?n th? sinh viên có ID là 0
			                cout << left << "|" << setw(3) << stt << "|" 
			                << setw(10) << student.id << "|"
			                << setw(24) << student.studentName << "|"
			                << setw(24) << student.dateOfBirth << "|"
			                << setw(14) << student.gender << "|" 
							<< setw(10) << student.studentClass << "|" << endl;
			                stt++;
			            }
			        }
			
			        cout << "|___|__________|________________________|________________________|______________|__________|" << endl;
			        cout << "\n";
			        cout << " ____________________________________ " << endl;
			        cout << "|1. Them thong tin sinh vien         |" << endl;
			        cout << "|2. Cap nhat thong tin sinh vien     |" << endl;
			        cout << "|3. Tim kiem thong tin sinh vien     |" << endl;
			        cout << "|4. Xoa thong tin sinh vien          |" << endl;
			        cout << "|0. Quay lai                         |" << endl;
			        cout << "|____________________________________|" << endl;
			        cout << "Nhap lua chon cua ban: ";
			        int subChoice;
			        cin >> subChoice;
			
			        switch (subChoice) {
			        	case 1: {
						    cout << "\n";
						    cout << " __________________________________________" << endl;
						    cout << "|            Them Sinh Vien                |" << endl;
						    cout << "|__________________________________________|" << endl;
						
						    int newStudentId; // Thêm bi?n d? luu ID nh?p t? bàn phím
						    cout << "Nhap ID sinh vien: ";
						    cin >> newStudentId;
						
						    // Ki?m tra xem ID dã t?n t?i chua
						    bool idExists = false;
						    for (const Student& student : students) {
						        if (student.id == newStudentId) {
						            idExists = true;
						            break;
						        }
						    }
						
						    if (idExists) {
						        cout << "Sinh vien co ID " << newStudentId << " da ton tai. Vui long chon ID khac." << endl;
						    } else {
						        string newStudentName, newStudentGender, newStudentDOB, newStudentClass;
						
						        cout << "Nhap ten sinh vien: ";
						        cin.ignore();
						        getline(cin, newStudentName);

						        // S? d?ng vòng l?p d? b?t bu?c nh?p dúng d?nh d?ng ngày tháng nam sinh
						        bool dateOfBirthEntered = false;
						        while (!dateOfBirthEntered) {
						            cout << "Nhap ngay thang nam sinh (dd/mm/yyyy): ";
						            getline(cin, newStudentDOB);
						
						            // Ki?m tra xem chu?i nh?p có d? d? dài và có dúng d?nh d?ng ngày tháng nam không
						            if (newStudentDOB.length() == 10 && newStudentDOB[2] == '/' && newStudentDOB[5] == '/') {
						                dateOfBirthEntered = true;
						            } else {
						                cout << "Nhap sai dinh dang ngay thang nam sinh. Vui long nhap lai!" << endl;
						            }
						        }
						        
						        cout << "Nhap gioi tinh sinh vien: ";
						        getline(cin, newStudentGender);
						
						        cout << "Nhap lop cua sinh vien: ";
						        getline(cin, newStudentClass);
						
						        Student newStudent(newStudentId, newStudentName, newStudentDOB, newStudentGender, newStudentClass);
						        students.push_back(newStudent);
						
						        cout << "Them sinh vien thanh cong!" << endl;
						    }
						    pressAnyKey();
						    break;
						}
			            case 2: {
			            	cout << "\n";
			            	cout << " __________________________________________" << endl;
						    cout << "|       Cap Nhat Thong Tin Sinh Vien       |" << endl;
						    cout << "|__________________________________________|" << endl;
						    cout << "Nhap ID sinh vien can cap nhat: ";
						    int studentIdToUpdate;
						    cin >> studentIdToUpdate;
						
						    bool found = false;
						    for (size_t i = 0; i < students.size(); ++i) {
						        if (students[i].id == studentIdToUpdate) {
						            string updatedStudentName, updatedStudentGender, updatedStudentDOB, updatedStudentClass;
						
						            cout << "Nhap ten moi cho sinh vien: ";
						            cin.ignore();
						            getline(cin, updatedStudentName);
						
						            // su dung vong lap bat buoc phai nhap dung dinh dang ngay thang nam sinh
						            bool dateOfBirthEntered = false;
						            while (!dateOfBirthEntered) {
						                cout << "Nhap ngay thang nam sinh moi (dd/mm/yyyy): ";
						                getline(cin, updatedStudentDOB);
						
						                // Kiem tra xem chuoi nhap có du do dai va co dung dinh dang ngay thang nam không
						                if (updatedStudentDOB.length() == 10 && updatedStudentDOB[2] == '/' && updatedStudentDOB[5] == '/') {
						                    dateOfBirthEntered = true;
						                } else {
						                    cout << "Nhap sai dinh dang ngay thang nam sinh. Vui long nhap lai!" << endl;
						                }
						            }
						            
						            cout << "Nhap gioi tinh moi cho sinh vien: ";
						            getline(cin, updatedStudentGender);
						            
									cout << "Nhap lop moi cho sinh vien: ";
            						getline(cin, updatedStudentClass);
						
						            students[i].studentName = updatedStudentName;
						            students[i].gender = updatedStudentGender;
						            students[i].dateOfBirth = updatedStudentDOB;
						            students[i].studentClass = updatedStudentClass;
						
						            cout << "Cap nhat thong tin thanh cong!" << endl;
						            found = true;
						            break;
						        }
						    }
						
						    if (!found) {
						        cout << "Khong tim thay sinh vien co ID " << studentIdToUpdate << endl;
						    }
						    pressAnyKey();
						    break;
			            }
			            case 3: {
			            	// Tim kiem sinh vien theo ID
							cout <<"\n";
						    cout << " __________________________________________" << endl;
						    cout << "|       Tim kiem thong tin sinh vien       |" << endl;
						    cout << "|__________________________________________|" << endl;
						    int searchId;
						    cout << "Nhap ID sinh vien can tim: ";
						    cin >> searchId;
						
						    bool found = false;
						
						    for (size_t i = 0; i < students.size(); ++i) {
						        if (students[i].id == searchId) {
						            // In thông tin sinh viên du?i d?ng b?ng v?i setw
						            
						            cout << "\n";
						            cout << " ______________________________________________________________________________________" << endl;
							        cout << "|                                Danh Sach Sinh Vien                                   |" << endl;
							        cout << "|______________________________________________________________________________________|" << endl;
							        cout << left << setw(11) << "|ID" << setw(25) << "|Ho va ten" << setw(25) << "|Ngay sinh" << setw(15) << "|Gioi tinh" << setw(11) << "|Lop" << "|" << endl;
							        cout << "|__________|________________________|________________________|______________|__________|" << endl;
						            
									cout << left << "|" << setw(10) << students[i].id << "|"
						            	<< setw(24) << students[i].studentName << "|"
						                << setw(24) << students[i].dateOfBirth << "|"
						                << setw(14) << students[i].gender << "|"
						            	<< setw(10) << students[i].studentClass << "|" << endl;
						                
						            cout << "|__________|________________________|________________________|______________|__________|" << endl;
						            found = true;
						            break;
						        }
						    }
						
						    if (!found) {
						        cout << "Khong tim thay sinh vien co ID " << searchId << endl;
						    }
						    pressAnyKey();
						    break;
						}
			            case 4: {
			            	cout << "\n";
			            	cout << " __________________________________________" << endl;
						    cout << "|          Xoa thong tin sinh vien         |" << endl;
						    cout << "|__________________________________________|" << endl;
			                cout << "Nhap ID sinh vien can xoa: ";
			                int studentIdToDelete;
			                cin >> studentIdToDelete;
			
			                bool found = false;
			                for (size_t i = 0; i < students.size(); ++i) {
			                    if (students[i].id == studentIdToDelete) {
			                        students.erase(students.begin() + i);
			                        cout << "Xoa sinh vien thanh cong!" << endl;
			                        found = true;
			                        break;
			                    }
			                }
			
			                if (!found) {
			                    cout << "Khong tim thay sinh vien co ID " << studentIdToDelete << endl;
			                }
			
			                break;
			            }
			            case 0: {
			                // Quay lai menu chinh
			                break;
			            }
			            default: {
			                cout << "Lua chon khong hop le. Vui long chon lai." << endl;
			                break;
			            }
			        }
			
			        if (subChoice == 0) {
			            break;  // Thoát khoi vòng lap while khi chon quay lai
			        }
			    }
			    break;
			}
			case 2: {
			    while (true) {
			        // Hien thi danh sach sinh viên
			        system("cls");
			        cout << " __________________________________________________________________________________________" << endl;
			        cout << "|                                    Danh Sach Sinh Vien                                   |" << endl;
			        cout << "|__________________________________________________________________________________________|" << endl;
			        cout << left << "|STT|" << setw(10) << "ID" << setw(25) << "|Ho va ten" << setw(25) << "|Ngay sinh" << setw(15) << "|Gioi tinh" << setw(11) << "|Lop" << "|" << endl;
			        cout << "|___|__________|________________________|________________________|______________|__________|" << endl;
			
			        int stt = 1; // So thu tu
			        for (const Student& student : students) {
			            if (student.id != 0) {  // Thêm di?u ki?n d? không hi?n th? sinh viên có ID là 0
			                cout << left << "|" << setw(3) << stt << "|" 
			                << setw(10) << student.id << "|"
			                << setw(24) << student.studentName << "|"
			                << setw(24) << student.dateOfBirth << "|"
			                << setw(14) << student.gender << "|" 
							<< setw(10) << student.studentClass << "|" << endl;
			                stt++;
			            }
			        }
			
			        cout << "|___|__________|________________________|________________________|______________|__________|" << endl;
			        cout << "\n";
			        cout << " ____________________________________ " << endl;
			        cout << "|1. Xem diem sinh vien               |" << endl;
			        cout << "|2. Cap nhap diem sinh vien          |" << endl;
			        cout << "|0. Quay lai                         |" << endl;
			        cout << "|____________________________________|" << endl;
			        cout << "Nhap lua chon cua ban: ";
			        int subChoice;
			        cin >> subChoice;
			
			        switch (subChoice) {
			            case 1: {
			            	cout << "\n";
			            	cout << "===== Xem Diem Cua Sinh Vien =====" << endl;
			            	cout << "\n";
					        cout << "Nhap ID sinh vien: ";
					        int studentIdToView;
					        cin >> studentIdToView;
					
					        bool found = false;
					        for (size_t i = 0; i < students.size(); ++i) {
					            if (students[i].id == studentIdToView) {
					            	cout << "ID: " << students[i].id << endl;
					                cout << "Ho va ten: " << students[i].studentName << endl;
					                cout << "Diem hoc tap:" << endl;
					                
					                cout << "\n";
					                
					                cout << " _________________________________________ " << endl;
					                cout << "|              Diem hoc tap               |" << endl;
					                cout << "|_________________________________________|" << endl;
					                cout << left << "|" << setw(30) << "ten mon hoc" << "|" << setw(10) << "Diem" << "|" << endl;
					                cout << "|______________________________|__________|" << endl;
					                for (const auto& grade : students[i].grades) {
					                	
					                    cout << left << "|" << setw(30) << grade.first << "|" << setw(10) << grade.second << "|" << endl;
					                }
					                cout << "|______________________________|__________|" << endl;
					                cout << left << "|" << setw(30) << "Diem Trung Binh" << "|" << setw(10) << students[i].calculateAverageGrade() << "|" << endl;
					                cout << "|______________________________|__________|" << endl;
					                found = true;
					                break;
					            }
					        }
					
					        if (!found) {
					            cout << "Khong tim thay sinh vien co ID " << studentIdToView << endl;
					        }
					        pressAnyKey();
					        break;
						}
			            case 2: {
			            	cout <<"\n";
					        cout << "===== Cap Nhap Diem Cho Sinh Vien =====" << endl;
					        cout << "\n";
					        cout << "Nhap ID sinh vien: ";
					        int studentIdToEdit;
					        cin >> studentIdToEdit;
					
					        bool found = false;
					        for (size_t i = 0; i < students.size(); ++i) {
					            if (students[i].id == studentIdToEdit) {
					                cout << "Ho va ten: " << students[i].studentName << endl;
					                cout << "ID: " << students[i].id << endl;
					                cout << "Diem hoc tap hien tai:" << endl;
					                
									cout << "\n";
					                
					                cout << " _________________________________________ " << endl;
					                cout << "|              Diem hoc tap               |" << endl;
					                cout << "|_________________________________________|" << endl;
					                cout << left << "|" << setw(30) << "ten mon hoc" << "|" << setw(10) << "Diem" << "|" << endl;
					                cout << "|______________________________|__________|" << endl;
					                for (const auto& grade : students[i].grades) {
					                	
					                    cout << left << "|" << setw(30) << grade.first << "|" << setw(10) << grade.second << "|" << endl;
					                }
					                cout << "|______________________________|__________|" << endl;
					
									cout << "\n";
					
					                string subject;
					                double newGrade;
					
					                cout << "Nhap ten mon hoc can cap nhap diem: ";
					                cin.ignore();
					                getline(cin, subject);
					
					                bool subjectFound = false;
					                for (auto& grade : students[i].grades) {
					                    if (grade.first == subject) {
					                        subjectFound = true;
					                        cout << "Nhap diem moi cho mon hoc " << subject << ": ";
					                        cin >> newGrade;
					                        grade.second = newGrade;
					                        cout << "Cap nhap diem thanh cong!" << endl;
					                        break;
					                    }
					                }
					
					                if (!subjectFound) {
					                    cout << "Khong tim thay mon hoc " << subject << " trong danh sach diem cua sinh vien." << endl;
					                }
					
					                found = true;
					                break;
					            }
					        }
					
					        if (!found) {
					            cout << "Khong tim thay sinh vien co ID " << studentIdToEdit << endl;
					        }
					        pressAnyKey();
					        break;
					    }
			            case 0: {
			                // Quay lai menu chinh
			                break;
			            }
			            default: {
			                cout << "Lua chon khong hop le. Vui long chon lai." << endl;
			                break;
			            }
			        }
			
			        if (subChoice == 0) {
			            break;  // Thoát khoi vòng lap while khi chon quay lai
			        }
			    }
			    break;
			}
			
			case 3: {
			    while (true) {
			        // Hien thi danh sach sinh viên
			        system("cls");
			        cout << " __________________________________________________________________________________________" << endl;
			        cout << "|                                    Danh Sach Sinh Vien                                   |" << endl;
			        cout << "|__________________________________________________________________________________________|" << endl;
			        cout << left << "|STT|" << setw(10) << "ID" << setw(25) << "|Ho va ten" << setw(25) << "|Ngay sinh" << setw(15) << "|Gioi tinh" << setw(11) << "|Lop" << "|" << endl;
			        cout << "|___|__________|________________________|________________________|______________|__________|" << endl;
			
			        int stt = 1; // So thu tu
			        for (const Student& student : students) {
			            if (student.id != 0) {  // Thêm di?u ki?n d? không hi?n th? sinh viên có ID là 0
			                cout << left << "|" << setw(3) << stt << "|" 
			                << setw(10) << student.id << "|"
			                << setw(24) << student.studentName << "|"
			                << setw(24) << student.dateOfBirth << "|"
			                << setw(14) << student.gender << "|" 
							<< setw(10) << student.studentClass << "|" << endl;
			                stt++;
			            }
			        }
			
			        cout << "|___|__________|________________________|________________________|______________|__________|" << endl;
			        cout << "\n";
			        cout << " _________________________________________________" << endl;
				    cout << "|             Quan Ly Mon Hoc Sinh Vien           |" << endl;
				    cout << "|_________________________________________________|" << endl;
				    cout << "|1. Dang ky mon hoc cho sinh vien                 |" << endl;
				    cout << "|2. Xoa mon hoc da dang ky                        |" << endl;
				    cout << "|3. Xem so mon hoc da dang ky cua sinh vien       |" << endl;
				    cout << "|0. Quay lai                                      |" << endl;
				    cout << "|_________________________________________________|" << endl;
			        cout << "Nhap lua chon cua ban: ";
			        int subChoice;
			        cin >> subChoice;
			
				    switch (subChoice) {
				        case 1: {
				        	cout << "\n";
				            int studentId;
				            cout << "Nhap ID sinh vien: ";
				            cin >> studentId;
				
				            bool found = false;
				            for (auto& student : students) {
				                if (student.id == studentId) {
				                    string subject;
				                    cout << "Nhap ten mon hoc (nhap 'q' de ket thuc): ";
				                    cin.ignore();
				                    getline(cin, subject);
				
				                    while (subject != "q" && subject != "Q") {
				                        student.addGrade(subject, 0.0);
				                        cout << "Dang ky mon hoc " << subject << " thanh cong!" << endl;
				
				                        cout << "Nhap ten mon hoc tiep theo (nhap 'q' de ket thuc): ";
				                        getline(cin, subject);
				                    }
				
				                    found = true;
				                    break;
				                }
				            }
				
				            if (!found) {
				                cout << "Khong tim thay sinh vien co ID " << studentId << endl;
				                pressAnyKey();
				                break;
				            }
				            
				            cout << "\nDanh sach mon hoc da dang ky cua sinh vien co ID " << studentId << ":\n";
				            cout << " ______________________________" << endl;
				            cout << left << "|" << setw(30) << "ten mon hoc" << "|" << endl;
				            cout << "|______________________________|" << endl;
				            for (const auto& student : students) {
				                if (student.id == studentId) {
				                    for (const auto& grade : student.grades) {
				                    	cout << left << "|" << setw(30) << grade.first << "|" << endl;
				                    }
				                    break;
				                }
				            }
				            cout << "|______________________________|" << endl;
				
				            pressAnyKey();
				            break;
				        }
				        case 2: {
				        	cout << "\n";
				            int studentId;
				            cout << "Nhap ID sinh vien: ";
				            cin >> studentId;
				
							cout << "\nDanh sach mon hoc da dang ky cua sinh vien co ID " << studentId << ":\n";
				            cout << " ______________________________" << endl;
				            cout << left << "|" << setw(30) << "ten mon hoc" << "|" << endl;
				            cout << "|______________________________|" << endl;
				            for (const auto& student : students) {
				                if (student.id == studentId) {
				                    for (const auto& grade : student.grades) {
				                    	cout << left << "|" << setw(30) << grade.first << "|" << endl;
				                    }
				                    break;
				                }
				            }
				            cout << "|______________________________|" << endl;
							
				            bool found = false;
				            for (auto& student : students) {
				                if (student.id == studentId) {
				                    string subject;
				                    cout << "\n";
				                    cout << "Nhap ten mon hoc can xoa (nhap 'q' de ket thuc): ";
				                    cin.ignore();
				                    getline(cin, subject);
				
				                    while (subject != "q" && subject != "Q") {
				                        auto it = find_if(student.grades.begin(), student.grades.end(),
				                                          [subject](const pair<string, float>& grade) {
				                                              return grade.first == subject;
				                                          });
				
				                        if (it != student.grades.end()) {
				                            student.grades.erase(it);
				                            cout << "Xoa mon hoc " << subject << " thanh cong!" << endl;
				                        } else {
				                            cout << "Mon hoc " << subject << " khong ton tai trong danh sach dang ky cua sinh vien." << endl;
				                        }
				
				                        cout << "Nhap ten mon hoc tiep theo (nhap 'q' de ket thuc): ";
				                        getline(cin, subject);
				                    }
				
				                    found = true;
				                    break;
				                }
				            }
				
				            if (!found) {
				                cout << "Khong tim thay sinh vien co ID " << studentId << endl;
				                pressAnyKey();
				                break;
				            }
				
				            cout << "\nDanh sach mon hoc da dang ky cua sinh vien co ID " << studentId << ":\n";
				            cout << " ______________________________" << endl;
				            cout << left << "|" << setw(30) << "ten mon hoc" << "|" << endl;
				            cout << "|______________________________|" << endl;
				            for (const auto& student : students) {
				                if (student.id == studentId) {
				                    for (const auto& grade : student.grades) {
				                    	cout << left << "|" << setw(30) << grade.first << "|" << endl;
				                    }
				                    break;
				                }
				            }
				            cout << "|______________________________|" << endl;
				
				            pressAnyKey();
				            break;
				        }
				        case 3: {
				        	cout << "\n";
						    int studentId;
						    cout << "Nhap ID sinh vien: ";
						    cin >> studentId;
						
						    bool found = false;
						    for (const auto& student : students) {
						        if (student.id == studentId) {
						            cout << "\nDanh sach mon hoc da dang ky cua sinh vien co ID " << studentId << ":\n";
						            cout << " ______________________________" << endl;
						            cout << left << "|" << setw(30) << "ten mon hoc" << "|" << endl;
						            cout << "|______________________________|" << endl;
						            for (const auto& grade : student.grades) {
						                cout << left << "|" << setw(30) << grade.first << "|" << endl;
						            }
						            cout << "|______________________________|" << endl;
						            found = true;
						            break;
						        }
						    }
						
						    if (!found) {
						        cout << "Khong tim thay sinh vien co ID " << studentId << endl;
						    }
						
						    pressAnyKey();
						    break;
						}
				        case 0: {
				            break;
				        }
				        default: {
				            cout << "Lua chon khong hop le. Vui long chon lai." << endl;
				            break;
				        }
				    }
			
			        if (subChoice == 0) {
			            break;  // Thoát khoi vòng lap while khi chon quay lai
			        }
			    }
			    break;
			}
			case 4: { // Lua chon moi: Luu du lieu sinh vien vao tep
                saveStudentsToFile(students);
                pressAnyKey();
                break;
            }
            case 0:
                return;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }
    }
}

void quanLyGiangVienMenu(vector<Professor>& professors) {
    while (true) {
        system("cls");
        cout << " ____________________________________"  << endl;
        cout << "|          Quan Ly Giang Vien        |" << endl;
        cout << "|____________________________________|" << endl;
        cout << "|1. Them giang vien                  |" << endl;
        cout << "|2. Cap nhat thong tin giang vien    |" << endl;
        cout << "|3. Xoa giang vien                   |" << endl;
        cout << "|4. Hien thi danh sach giang vien    |" << endl;
        cout << "|0. Tro ve menu chinh                |" << endl;
        cout << "|____________________________________|" << endl;
        cout << "Nhap lua chon cua ban: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
            	cout << "\n";
            	cout << "===== Them thong tin giang vien =====" << endl;
            	cout << "\n";
                string newProfessorName, newCourseTeaching;
			    cout << "Nhap ten giang vien: ";
			    cin.ignore();
			    getline(cin, newProfessorName);
			    cout << "Nhap mon hoc giang day: ";
			    getline(cin, newCourseTeaching);
			
			    Professor newProfessor(newProfessorName, newCourseTeaching);
			    professors.push_back(newProfessor);
			    cout << "Them giang vien thanh cong!" << endl;
			    pressAnyKey();
			    break;
            }
            case 2: {
            	cout << "\n";
            	cout << "===== Cap nhap thong tin giang vien =====" << endl;
            	cout << "\n";
                cout << "Nhap ten giang vien can cap nhat thong tin: ";
			    cin.ignore();
			    string professorNameToUpdate;
			    getline(cin, professorNameToUpdate);
			
			    bool found = false;
			    for (size_t i = 0; i < professors.size(); ++i) {
			        if (professors[i].professorName == professorNameToUpdate) {
			            string updatedProfessorName, updatedCourseTeaching;
			
			            cout << "Nhap ten moi cho giang vien: ";
			            getline(cin, updatedProfessorName);
			            cout << "Nhap mon hoc giang day moi: ";
			            getline(cin, updatedCourseTeaching);
			
			            professors[i].professorName = updatedProfessorName;
			            professors[i].courseTeaching = updatedCourseTeaching;
			
			            cout << "Cap nhat thong tin thanh cong!" << endl;
			            found = true;
			            break;
			        }
			    }
			
			    if (!found) {
			        cout << "Khong tim thay giang vien co ten " << professorNameToUpdate << endl;
			    }
			    pressAnyKey();
			    break;
            }
            case 3: {
            	cout << "\n";
            	cout << "===== Xoa thong tin giang vien =====" << endl;;
            	cout << "\n";
                cout << "Nhap ten giang vien can xoa: ";
                cin.ignore();
                string professorNameToDelete;
                getline(cin, professorNameToDelete);

                bool found = false;
                for (size_t i = 0; i < professors.size(); ++i) {
                    if (professors[i].professorName == professorNameToDelete) {
                        professors.erase(professors.begin() + i);
                        cout << "Xoa giang vien thanh cong!" << endl;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Khong tim thay giang vien co ten " << professorNameToDelete << endl;
                }
                pressAnyKey();
                break;
            }
            case 4: {
                cout << "\n";
                cout << "=== Danh Sach Giang Vien ===" << endl;
			    cout << left << setw(10) <<  "STT" << setw(20) << "Ten Giang Vien" << setw(20) << "Mon Hoc Giang Day" << endl;
			    cout << "----------------------------------------------------" << endl;
			
			    int stt = 1; // So thu tu
			    for (const Professor& professor : professors) {
			        cout << setw(10) << stt << setw(20) << professor.professorName << setw(20) << professor.courseTeaching << endl;
			        stt++;
			    }
			
			    pressAnyKey();
			    break;
            }
            case 0:
                return;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }
    }
}

int main() {
    int choice;
    vector<User> registeredUsers;
    bool loggedIn = false;
    vector<Student> students;
    vector<Professor> professors;
    loadStudentsFromFile(students);
    loadRegisteredUsersFromFile(registeredUsers);

    while (true) {
    	system("color 4");
        if (!loggedIn) {
        	cout << " __________________________________________ " << endl;
            cout << "|         MENU DANG KY VA DANG NHAP        |" << endl;
            cout << "|__________________________________________|" << endl;
            cout << "|1. Dang ky                                |" << endl;
            cout << "|2. Dang nhap                              |" << endl;
            cout << "|3. Thoat                                  |" << endl;
            cout << "|__________________________________________|" << endl;
            cout << "Nhap lua chon cua ban: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    string newUsername, newPassword;
                    bool userExists = false;
                    cout << " ____________________________ " << endl;
                    cout << "|           DANG KY          |" << endl;
					cout << "|____________________________|" << endl;
                    cout << "Nhap ten nguoi dung:";
                    cin >> newUsername;

                    for (size_t i = 0; i < registeredUsers.size(); ++i) {
                        if (registeredUsers[i].username == newUsername) {
                            userExists = true;
                            break;
                        }
                    }

                    if (userExists) {
                        cout << "Ten nguoi dung da ton tai. Vui long chon ten khac." << endl;
                    } else {
                        cout << "Nhap mat khau:" << endl;
                        cin >> newPassword;
                        User newUser(newUsername, newPassword);
                        registeredUsers.push_back(newUser);
                        saveRegisteredUsersToFile(registeredUsers);
                        cout << "Dang ky thanh cong!" << endl;
                    }
                    pressAnyKey();
                    break;
                }
                case 2: {
                    string inputUsername, inputPassword;
                    cout << " ____________________________" << endl;
                    cout << "|          DANG NHAP         | " << endl;
					cout << "|____________________________|" << endl;
                    cout << "Nhap ten nguoi dung: ";
                    cin >> inputUsername;
                    cout << "Nhap mat khau: ";
                    cin >> inputPassword;

                    loggedIn = false;
                    for (size_t i = 0; i < registeredUsers.size(); ++i) {
                        if (registeredUsers[i].Login(inputUsername, inputPassword)) {
                            loggedIn = true;
                            cout << "Dang nhap thanh cong!" << endl;
                            break;
                        }
                    }

                    if (!loggedIn) {
                        cout << "Dang nhap that bai. Ten nguoi dung hoac mat khau khong chinh xac." << endl;
                    }
                    pressAnyKey();
                    break;
                }
                case 3:
                    cout << "Ban da chon thoat. Tam biet!" << endl;
                    return 0;
                default:
                    cout << "Lua chon khong hop le. Vui long chon lai." << endl;
            }
        } else {
            // Hien thi menu chinh sau khi dang nhap thanh cong
            system("color 9");
            system("cls");
            cout << " ____________________________ " << endl;
            cout << "|         MENU CHINH         |" << endl;
            cout << "|____________________________|" << endl;
            cout << "|1. Quan Ly Sinh Vien        |" << endl;
            cout << "|2. Quan Ly Giang Vien       |" << endl;
            cout << "|3. Thoat                    |" << endl;
            cout << "|____________________________|" << endl;
            cout << "\n";
            cout << "Nhap lua chon cua ban: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    quanLySinhVienMenu(students);
                    break;
                case 2:
                    quanLyGiangVienMenu(professors);
                    break;
                case 3:
                    loggedIn = false; // Ðang xuat
                    cout << "Ban da dang xuat." << endl;
                    pressAnyKey();
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long chon lai." << endl;
            }
        }
    }

    return 0;
}

