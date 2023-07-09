#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct Student
{
    int student_id;
    char name[20];
    char group_partner[20];
    int group_id;
    char assignment_name[20];
    char deadline[20];
    char status[20];
    int evaluation_marks;
    int viva_marks;
    struct Student* next;
}Student;
Student* createStudent(int student_id, char name[], char group_partner[], int group_id, char assignment_name[], char deadline[], char status[], int evaluation_marks, int viva_marks) 
{
    Student* newStudent = (Student*)malloc(sizeof(Student));
    newStudent->student_id = student_id;
    strcpy(newStudent->name, name);
    strcpy(newStudent->group_partner, group_partner);
    newStudent->group_id = group_id;
    strcpy(newStudent->assignment_name, assignment_name);
    strcpy(newStudent->deadline, deadline);
    strcpy(newStudent->status, status);
    newStudent->evaluation_marks = evaluation_marks;
    newStudent->viva_marks = viva_marks;
    newStudent->next = NULL;
    return newStudent;
}
/*void input()
{
    int student_id;
    char name[20];
    char group_partner[20];
    int group_id;
    char assignment_name[20];
    char deadline[20];
    char status[20];
    int evaluation_marks;
    int viva_marks;
    printf("\n enter student id: ");
    scanf("%d",student_id);
    printf("\n enter student name: ");
    scanf("%s",name);
    printf("\n enter group partner name: ");
    scanf("%s",group_partner);
    printf("\n enter group id: ");
    scanf("%d",group_id);
    printf("\n enter assignment name: ");
    scanf("%s",assignment_name);
    printf("\n enter deadline: ");
    scanf("%s",deadline);
    printf("\n enter status: ");
    scanf("%s",status);
    printf("\n enter evaluation marks: ");
    scanf("%d",evaluation_marks);
    printf("\n enter viva marks: ");
    scanf("%d",viva_marks);
    createStudent(student_id, name, group_partner, group_id, assignment_name, deadline, status, evaluation_marks, viva_marks);
}*/
void addStudent(Student** head, Student* newStudent) 
{
    if (*head == NULL) 
    {
        *head = newStudent;
        return;
    }
    Student* current = *head;
    while (current->next != NULL) 
    {
        current = current->next;
    }
    current->next = newStudent;
}
void printStudents(Student* head) 
{
    Student* current = head;
    while (current != NULL) 
    {
        printf("Student ID: %d\n", current->student_id);
        printf("Name: %s\n", current->name);
        printf("Group Partner: %s\n", current->group_partner);
        printf("Group ID: %d\n", current->group_id);
        printf("Assignment Name: %s\n", current->assignment_name);
        printf("Deadline: %s\n", current->deadline);
        printf("Status: %s\n", current->status);
        printf("Evaluation Marks: %d\n", current->evaluation_marks);
        printf("Viva Marks: %d\n", current->viva_marks);
        printf("\n");
        current = current->next;
    }
}
struct asgn_rec
{
    int asgn_id;
    char topic[20];
    char status[20];
    struct asgn_rec* right;
    struct asgn_rec* down;

};
int main() 
{
    // Create some sample student records
    Student* student1 = createStudent(1, "Alice", "", 1, "Assignment 1", "2023-03-31", "Not Submitted", 0, 0);
    Student* student2 = createStudent(2, "Bob", "", 1, "Assignment 1", "2023-03-31", "Not Submitted", 0, 0);
    Student* student3 = createStudent(3, "Charlie", "David", 2, "Assignment 2", "2023-04-30", "Submitted", 80, 85);

    // Add the student records to the linked list
    Student* head = NULL;
    addStudent(&head, student1);
    addStudent(&head, student2);
    addStudent(&head, student3);
    printStudents(head);
    return 0;
}