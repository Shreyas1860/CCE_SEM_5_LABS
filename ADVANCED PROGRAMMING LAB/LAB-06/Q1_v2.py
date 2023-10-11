import firebase_admin
from firebase_admin import credentials,db


cred = credentials.Certificate("credentials.json")
firebase_admin.initialize_app(cred, {"databaseURL": "https://ap-lab-75fd2-default-rtdb.asia-southeast1.firebasedatabase.app/"})



def add_student(student_id, student_name, student_grade):
    students_ref = db.reference("students")
    student_data = {
        "name": student_name,
        "grade": student_grade
    }
    students_ref.child(student_id).set(student_data)

def get_student(student_id):
    students_ref = db.reference("students")
    student = students_ref.child(student_id).get()
    return student

def list_students():
    students_ref = db.reference("students")
    return students_ref.get()

def main():
    while True:
        print("Student Management System")
        print("1. Add Student")
        print("2. Get Student")
        print("3. List Students")
        print("4. Quit")

        choice = input("Enter your choice: ")

        if choice == "1":
            student_id = input("Enter Student ID: ")
            student_name = input("Enter Student Name: ")
            student_grade = input("Enter Student Grade: ")
            add_student(student_id, student_name, student_grade)
            print("Student added successfully!")

        elif choice == "2":
            student_id = input("Enter Student ID: ")
            student = get_student(student_id)
            if student:
                print(f"Student Name: {student['name']}")
                print(f"Student Grade: {student['grade']}")
            else:
                print("Student not found!")

        elif choice == "3":
            students = list_students()
            print("List of Students:")
            for student_id, student_data in students.items():
                print(f"ID: {student_id}, Name: {student_data['name']}, Grade: {student_data['grade']}")

        elif choice == "4":
            break

if __name__ == "__main__":
    main()



