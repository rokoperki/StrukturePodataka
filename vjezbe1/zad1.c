#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char surname[50];
    int points;
} Student;

int count_lines(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    int lines = 0;
    char buffer[150];
    while (fgets(buffer, sizeof(buffer), file)) {
        lines++;
    }
    fclose(file);
    return lines;
}

void read_students(const char *filename, Student *students, int count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < count; i++) {
        fscanf(file, "%s %s %d", students[i].name, students[i].surname, &students[i].points);
    }
    fclose(file);
}

int find_max_points(Student *students, int count) {
    int max_points = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].points > max_points) {
            max_points = students[i].points;
        }
    }
    return max_points;
}

void print_students(Student *students, int count, int max_points) {
    for (int i = 0; i < count; i++) {
        double relative_points = (double)students[i].points / max_points * 100;
        printf("%s %s: %d (%.2f%%)\n", students[i].name, students[i].surname, students[i].points, relative_points);
    }
}

int main() {
    const char *filename = "zad1.txt";
    int student_count = count_lines(filename);

    Student *students = (Student *)malloc(student_count * sizeof(Student));
    if (!students) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    read_students(filename, students, student_count);
    int max_points = find_max_points(students, student_count);
    print_students(students, student_count, max_points);

    free(students);
    return 0;
}