
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <cstring>
using namespace std;


// Plugboard - Select what letters are plugged together, default is none. Optional do random selector
static void PlugBoard(string(&arr_of_mappings)[13])
{
    cout << "Please Choose what letters are linked together in the plugboard.\n";
    cout << "For example if want A to be mapped to H and thus H to A, then type AH.\n";
    cout << "Press 1 to finish.\n";

    //Defing variables
    bool linking_letters = true;
    int counter_for_index = 0;

    //List to have the first letters in for error checking of multiple mappings of the same letter.
    list<string> list_of_mappings{};

    while (linking_letters) {
        //Getting the letters to be mapped
        string Mapping;
        cout << "Enter 1st letter to be mapped to 2nd letter: ";
        cin >> Mapping;

        transform(Mapping.begin(), Mapping.end(), Mapping.begin(), ::toupper);

        //Checking if the letter mapped has already been mapped
        bool found = false;
        for (string const& letter : list_of_mappings) {
            if ((letter[0] == Mapping[0]) || (letter[0] == Mapping[1])) {
                found = true;
            }
            else if ((letter[1] == Mapping[0]) || (letter[1] == Mapping[1])) {
                found = true;
            }
        }

        //Checking to see if want to finish mapping letters
        if (Mapping == "1") {
            linking_letters = false;
        }
        else if (Mapping[0] == Mapping[1]) {
            cout << "Sorry, cannot map letter to itself.\n";
        }
        //Error printed if first letter has been used before
        else if (found == true) {
            cout << "Sorry, letter has already been mapped.\n";
        }
        else if (Mapping.size() != 2) {
            cout << "Sorry, only 2 letters should be provided.\n";
        }
        //Adding the mapping to the array and the first letter to the list of first letters
        else {
            //adding the mapping to the array
            arr_of_mappings[counter_for_index] = Mapping;
            list_of_mappings.emplace_back(Mapping);
            counter_for_index++;
        }
    }
}



class Rotors {
private:
    //Have Attribute of the rotors, given the code in the defining of rotor.
    char rotor1_letters[26];
    char rotor2_letters[26];
    char rotor3_letters[26];
    char alphabet[26];

    int shift_of_rotor1;
    int shift_of_rotor2;
    int shift_of_rotor3;

public:


    Rotors(char(&rotor1)[26], char(&rotor2)[26], char(&rotor3)[26], char(&received_alphabet)[26]) {
        //Constructor, setting the rotor attributes 

        int rotor1_counter = 0;
        for (char letter : rotor1) {
            rotor1_letters[rotor1_counter] = letter;
            rotor1_counter++;
        }

        int rotor2_counter = 0;
        for (char letter : rotor2) {
            rotor2_letters[rotor2_counter] = letter;
            rotor2_counter++;
        }

        int rotor3_counter = 0;
        for (char letter : rotor3) {
            rotor3_letters[rotor3_counter] = letter;
            rotor3_counter++;
        }

        int alphabet_counter = 0;
        for (char letter : received_alphabet) {
            alphabet[alphabet_counter] = letter;
            alphabet_counter++;
        }


        //Setting the inital settings for the rotors.
        char received_starting_position_rotor1;
        char received_starting_position_rotor2;
        char received_starting_position_rotor3;
        cout << "Please enter starting ring setting for the 3 rotors stating with the 1st rotor: \n";

        cin >> received_starting_position_rotor1;
        cin >> received_starting_position_rotor2;
        cin >> received_starting_position_rotor3;

        received_starting_position_rotor1 = toupper(received_starting_position_rotor1);
        received_starting_position_rotor2 = toupper(received_starting_position_rotor2);
        received_starting_position_rotor3 = toupper(received_starting_position_rotor3);

        //Getting the corresponding index of the letter from the alphabet.
        // And then shifting the rotors by that index amount
        // 
        //Rotor 1
        char* rotor1_alphabet_target_ptr = find(&alphabet[0], alphabet + 26, received_starting_position_rotor1);
        int index_received_starting_position_rotor1_alphabet = rotor1_alphabet_target_ptr - alphabet;
        Rotor1_Shift(index_received_starting_position_rotor1_alphabet);


        //Rotor 2
        char* rotor2_alphabet_target_ptr = find(&alphabet[0], alphabet + 26, received_starting_position_rotor2);
        int index_received_starting_position_rotor2_alphabet = rotor2_alphabet_target_ptr - alphabet;
        Rotor2_Shift(index_received_starting_position_rotor2_alphabet);

        //Rotor 3
        char* rotor3_alphabet_target_ptr = find(&alphabet[0], alphabet + 26, received_starting_position_rotor3);
        int index_received_starting_position_rotor3_alphabet = rotor3_alphabet_target_ptr - alphabet;
        Rotor3_Shift(index_received_starting_position_rotor3_alphabet);



        shift_of_rotor1 = index_received_starting_position_rotor1_alphabet;
        shift_of_rotor2 = index_received_starting_position_rotor2_alphabet;
        shift_of_rotor3 = index_received_starting_position_rotor3_alphabet;

    }

    void Rotor1_Shift(int shift_count) {
        for (int j = 0; j < shift_count; j++)
        {
            int temp1 = rotor1_letters[0]; //remember first element
            for (int i = 0;i < 25;i++)
            {
                rotor1_letters[i] = rotor1_letters[i + 1]; //move all element to the left except first one
            }
            rotor1_letters[25] = temp1; //assign remembered value to last element
        }
    }

    void Rotor2_Shift(int shift_count) {
        for (int j = 0; j < shift_count; j++)
        {
            int temp1 = rotor2_letters[0]; //remember first element
            for (int i = 0;i < 25;i++)
            {
                rotor2_letters[i] = rotor2_letters[i + 1]; //move all element to the left except first one
            }
            rotor2_letters[25] = temp1; //assign remembered value to last element
        }
    }

    void Rotor3_Shift(int shift_count) {
        for (int j = 0; j < shift_count; j++)
        {
            int temp1 = rotor3_letters[0]; //remember first element
            for (int i = 0;i < 25;i++)
            {
                rotor3_letters[i] = rotor3_letters[i + 1]; //move all element to the left except first one
            }
            rotor3_letters[25] = temp1; //assign remembered value to last element
        }
    }

    int Rotor_Traversal(char(&rotorN_letters)[26], int shift_of_rotorN, int last_updated_index_new_letterN_alphabet, char(&indexing_array)[26], bool left_direction) {


        //Finding the letter at that index
        char rotorN_corresponding_letter;


        if (left_direction == false) {
            // if last_updated_index_new_letterN_alphabet + shift_of_rotorN > 26 then minus 26 until it is.

            int combined_index = last_updated_index_new_letterN_alphabet + shift_of_rotorN;

            while (combined_index < 0) {
                combined_index = combined_index + 26;
            }

            while (combined_index > 25) {
                combined_index = combined_index - 26;
            }

            rotorN_corresponding_letter = rotorN_letters[combined_index];
        }
        else {

            while (last_updated_index_new_letterN_alphabet < 0) {
                last_updated_index_new_letterN_alphabet = last_updated_index_new_letterN_alphabet + 26;
            }

            while (last_updated_index_new_letterN_alphabet > 25) {
                last_updated_index_new_letterN_alphabet = last_updated_index_new_letterN_alphabet - 26;
            }

            rotorN_corresponding_letter = rotorN_letters[last_updated_index_new_letterN_alphabet];
        }

        //This is the index of that letter from the array
        char* rotor2_target_ptr = find(&indexing_array[0], indexing_array + 26, rotorN_corresponding_letter);
        int index_new_letterN_alphabet = rotor2_target_ptr - indexing_array;

        // Accounting for any inital starting point shift
        if (left_direction == true) {
            index_new_letterN_alphabet = index_new_letterN_alphabet - shift_of_rotorN;
        }
        else {
            index_new_letterN_alphabet = index_new_letterN_alphabet;// +shift_of_rotorN;

        }

        return index_new_letterN_alphabet;
    }

    void Display_The_Rotors() {
        cout << "To left: " << endl;
        for (int i = 0;i < 26;i++)
            cout << rotor1_letters[i] << endl;

        cout << "\nTo left: " << endl;
        for (int i = 0;i < 26;i++)
            cout << rotor2_letters[i] << endl;

        cout << "\nTo left: " << endl;
        for (int i = 0;i < 26;i++)
            cout << rotor3_letters[i] << endl;
    }

    char Encrypt(char letter_to_be_encrypted) {
        //Reflector A
        char reflector_letters[26] = { 'E','J','M','Z','A','L','Y','X','V','B','W','F','C','R','Q','U','O','N','T','S','P','I','K','H','G','D' };


        //For rotor 3
        //

        //Rotating the rotor once before first encrypting
        Rotor3_Shift(1);
        //Adding 1 to the shift of rotor 3.
        shift_of_rotor3++;


        //Getting the pointer of the alphabet
        char* target_ptr = find(&alphabet[0], alphabet + 26, letter_to_be_encrypted);
        // getting index from alphabet array of letter_to_be_encrypted
        int index_letterTBE_alphabet = target_ptr - alphabet;

        //Traversing the Rotor, going from index, to same letter in the shifted alphabet, and finding that index.
        int updated_index_new_letter3_alphabet = Rotor_Traversal(rotor3_letters, shift_of_rotor3, index_letterTBE_alphabet, alphabet, true);


        // For rotor 2
        //

        //Checking to see if the previous rotor (3) has stepped from V to W.
        if (shift_of_rotor3 == 22) {
            Rotor2_Shift(1);
            //Adding 1 to the shift of rotor 2.
            shift_of_rotor2++;
        }

        //Traversing the Rotor
        int updated_index_new_letter2_alphabet = Rotor_Traversal(rotor2_letters, shift_of_rotor2, updated_index_new_letter3_alphabet, alphabet, true);


        // For rotor 3
        //

        //Checking to see if the previous rotor (2) has stepped from E to F.
        if (shift_of_rotor2 == 5) {
            Rotor3_Shift(1);
            //Adding 1 to the shift of rotor 1.
            shift_of_rotor3++;
        }

        //Traversing the Rotor
        int updated_index_new_letter1_alphabet = Rotor_Traversal(rotor1_letters, shift_of_rotor1, updated_index_new_letter2_alphabet, alphabet, true);


        // For Reflector
        //

        int updated_index_new_letterR_alphabet = Rotor_Traversal(alphabet, 0, updated_index_new_letter1_alphabet, reflector_letters, true);


        // Rotor 1 Reverse
        //

        int updated_index_new_letterR1_alphabet = Rotor_Traversal(alphabet, shift_of_rotor1, updated_index_new_letterR_alphabet, rotor1_letters, false);


        // Rotor 2 Reverse
        //

        int updated_index_new_letterR2_alphabet = Rotor_Traversal(alphabet, shift_of_rotor2, updated_index_new_letterR1_alphabet, rotor2_letters, false);


        // Rotor 3 Reverse
        //

        int updated_index_new_letterR3_alphabet = Rotor_Traversal(alphabet, shift_of_rotor3, updated_index_new_letterR2_alphabet, rotor3_letters, false);


        //Finding out what the final letter is.

        char final_letter_before_plugboard = alphabet[updated_index_new_letterR3_alphabet];

        return final_letter_before_plugboard;

    }

};



int main()
{
    // Creating the arr_of_mappings here, passing it in by reference.

    string arr_of_mappings[13];

    PlugBoard(arr_of_mappings);


    //Setting up the rotor initial positions.

    //Rotor wiring tables 7th  February 1941	German Railway (Rocket)
    char arr_rotor1_letters[26] = { 'E','K','M','F','L','G','D','Q','V','Z','N','T','O','W','Y','H','X','U','S','P','A','I','B','R','C','J' };
    char arr_rotor2_letters[26] = { 'A','J','D','K','S','I','R','U','X','B','L','H','W','T','M','C','Q','G','Z','N','P','Y','F','V','O','E' };
    char arr_rotor3_letters[26] = { 'B','D','F','H','J','L','C','P','R','T','X','V','Z','N','Y','E','I','W','G','A','K','M','U','S','Q','O' };
    char arr_alphabet[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

    Rotors EnigmaRotors(arr_rotor1_letters, arr_rotor2_letters, arr_rotor3_letters, arr_alphabet);

    bool entering_letters = true;
    list<char> list_of_encrypted_letters{};

    cout << "If you wish to stop entering letters, press 1. \n";

    // Main loop
    while (entering_letters == true) {
        char letter_to_be_encrypted;
        cout << "Please enter a letter(s) you would like to encrypt:\n";
        cin >> letter_to_be_encrypted;

        if (letter_to_be_encrypted == '1') {
            entering_letters = false;
            break;
        }

        //Converting to uppercase
        letter_to_be_encrypted = toupper(letter_to_be_encrypted);

        //Checks to see if entered letter has a mapping, if so changes the enter letter.
        for (string letterMappings : arr_of_mappings) {

            int length_of_letter_mappings = letterMappings.size();

            if (length_of_letter_mappings == 2) {
                if (letterMappings[0] == letter_to_be_encrypted) {
                    letter_to_be_encrypted = letterMappings[1];
                    break;
                }
                if (letterMappings[1] == letter_to_be_encrypted) {
                    letter_to_be_encrypted = letterMappings[0];
                    break;
                }
            }

        }

        //Calling the rotor encrypt function to encrypt the letter with the rotors
        char final_letter = EnigmaRotors.Encrypt(letter_to_be_encrypted);

        //Plug Board
        //Checks to see if entered letter has a mapping, if so changes the enter letter.
        for (string letterMappings : arr_of_mappings) {

            int length_of_letter_mappings = letterMappings.size();

            if (length_of_letter_mappings == 2) {
                if (letterMappings[0] == final_letter) {
                    final_letter = letterMappings[1];
                    break;
                }
                if (letterMappings[1] == final_letter) {
                    final_letter = letterMappings[0];
                    break;
                }
            }

        }

        list_of_encrypted_letters.emplace_back(final_letter);


    }

    cout << "Encryption:\n";


    if (list_of_encrypted_letters.size() == 0) {
        cout << "No letters have been provided for encryption";
    } 
    else {
        for (char letters : list_of_encrypted_letters) {
        cout << letters << " ";
        }
    }

    


    return 0;
}


