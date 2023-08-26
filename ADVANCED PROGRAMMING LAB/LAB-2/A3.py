def create_text_file('sample_text.txt'):
    content = """Hello, this is line 1.
This is line 2 of the text file.
Line 3 is just an example.
Here comes line number four.
Fifth line is shorter.
Line number six reporting in.
Seventh line, reporting for duty!
The eighth and final line."""

    with open('sample_text.txt', 'w') as file:
        file.write(content)


def read_and_process_file('sample_text.txt'):
    line_data = {}
    letter_freq = {}

    with open('sample_text.txt', 'r') as file:
        lines = file.readlines()

        for line_num, line in enumerate(lines, start=1):
            line = line.strip()
            line_data[line_num] = {'string': line, 'length': len(line)}

            for char in line:
                if char.isalpha():
                    char = char.lower()
                    letter_freq[char] = letter_freq.get(char, 0) + 1

    print("Data using line numbers as keys and string info as values:")
    for key, value in line_data.items():
        print(f"Line {key}: {value['string']} (Length: {value['length']})")

    print("\nLetter frequency dictionary:")
    for char, freq in letter_freq.items():
        print(f"'{char}': {freq}")


# Step 1: Create a text file
create_text_file('sample_text.txt')

# Step 2 and 3: Read and process the file
read_and_process_file('sample_text.txt')