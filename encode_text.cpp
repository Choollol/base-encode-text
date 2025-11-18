#include <cctype>
#include <string>

#include "iostream"

std::string convertToBase(int base, int n) {
    std::string output;
    while (n > 0) {
        output.insert(0, std::to_string(n % base));
        n /= base;
    }
    return output;
}

// Assumes lowercase and 1-indexed
int getAlphabetIndex(char c) {
    return c - 'a' + 1;
}

int charToInt(char c) {
    return c - '0';
}

/**
 * Encodes a lowercase string by converting each character into a base `base` string
 * then converting each digit into a character.
 * @param text The input text.
 * @param base The base number to convert to.
 * @param cipherKey The characters to convert integral digits to. Length should equal `base`.
 * @param charSeparator The character to separate consecutive encoded-letters with.
 */
std::string getEncodedString(
    const std::string_view text,
    const int base,
    const std::string_view cipherKey,
    char charSeparator) {
    std::string output;
    for (const char c : text) {
        if (std::isalpha(c)) {
            std::string converted = convertToBase(3, getAlphabetIndex(c));
            for (const char convertedChar : converted) {
                output += cipherKey[charToInt(convertedChar)];
            }
            output += charSeparator;
        }
        else {
            output += c;
        }
    }
    return output;
}

int main(int argc, char* argv[]) {
    static constexpr int EXPECTED_ARGC = 5;
    if (argc != EXPECTED_ARGC) {
        std::cerr << "Error: Expected " << EXPECTED_ARGC << " arguments" << std::endl;
        exit(1);
    }
    const int base = std::stoi(argv[1]);
    const std::string digitCharMap(argv[2]);
    const char charSeparator = argv[3][0];
    const std::string inputText(argv[4]);

    const std::string output = getEncodedString(inputText, base, digitCharMap, charSeparator);

    std::cout << output << std::endl;
}