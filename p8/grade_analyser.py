MIN_GRADE = 0
MAX_GRADE = 100
PASS_MARK = 50
HD_MARK = 80


def read_integer(prompt):
    """Reads a whole number from the user, asking again until the input is valid."""
    line = input(prompt)

    while not line.strip().isdigit():
        print("Please enter a whole number")
        line = input(prompt)

    return int(line)


def read_integer_range(prompt, low, high):
    """Reads a whole number between low and high (inclusive)."""
    value = read_integer(prompt)

    while value < low or value > high:
        print(f"Please enter a number between {low} and {high}")
        value = read_integer(prompt)

    return value


def read_grades():
    """Asks how many grades to enter, then reads each one from the user."""
    grades = []
    count = read_integer_range("How many grades? ", 1, 100)

    for i in range(count):
        grades.append(read_integer_range(f"Enter grade {i + 1}: ", MIN_GRADE, MAX_GRADE))

    return grades


def average(grades):
    """Calculates the average of the grades."""
    total = 0

    for grade in grades:
        total += grade

    return total / len(grades)


def pass_rate(grades):
    """Calculates the percentage of grades that are a pass (50 or more)."""
    passes = 0

    for grade in grades:
        if grade >= PASS_MARK:
            passes += 1

    return passes * 100 / len(grades)


def count_hd(grades):
    """Counts how many grades are a high distinction (80 or more)."""
    hds = 0

    for grade in grades:
        if grade >= HD_MARK:
            hds += 1

    return hds


def main():
    print("Student Grade Analyser")

    grades = read_grades()

    print()
    print(f"Average grade: {average(grades)}")
    print(f"Pass rate: {pass_rate(grades)}%")
    print(f"High distinctions: {count_hd(grades)}")


if __name__ == "__main__":
    main()