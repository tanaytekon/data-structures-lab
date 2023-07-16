#include "IO.h"
#include "ApartmentList.h"
#include <fstream>

// Reads and executes all commands in input file, and writes to output file.
void readAndExecuteCommands(string inputFileName, string outputFileName) {

    ApartmentList* apartmentList = new ApartmentList();
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);
    string line;
    // For each line in input
    while (getline (inputFile, line)) {

        // Command to vector
        vector<string> arguments;
        // Delete "\r" character
        line = line.substr(0,line.find("\r"));
        // While there is "\t" character
        while(line.find("\t") < line.size()) {
            arguments.push_back(line.substr(0, line.find("\t")));
            line = line.substr(line.find("\t")+1);
        }
        arguments.push_back(line);

        // Execute command
        string command = arguments.front();
        if(command=="add_apartment") {
            apartmentList->add_apartment(arguments.at(1),arguments.at(2),stoi(arguments.at(3)));
            continue;
        }
        if(command=="add_flat") {
            apartmentList->add_flat(arguments.at(1),stoi(arguments.at(2)),stoi(arguments.at(3)),stoi(arguments.at(4)));
            continue;
        }
        if(command==("remove_apartment")) {
            ApartmentList* returnedList = apartmentList->remove_apartment(arguments.at(1));
            continue;
        }
        if(command=="make_flat_empty") {
            apartmentList->make_flat_empty(arguments.at(1),stoi(arguments.at(2)));
            continue;
        }
        if(command=="find_sum_of_max_bandwidths") {
            outputFile << "sum of bandwidth: " << apartmentList->find_sum_of_max_bandwidths() << "\n\n";
            continue;
        }
        if(command=="merge_two_apartments") {
            apartmentList->merge_two_apartments(arguments.at(1),arguments.at(2));
            continue;
        }
        if(command=="relocate_flats_to_same_apartment") {
            // flat_id_list to vector
            string flat_id_list_str = arguments.at(3);
            vector<int> flat_id_list;
            flat_id_list_str = flat_id_list_str.substr(1, flat_id_list_str.size()-2);
            string delimiter = ",";
            while(flat_id_list_str.find(delimiter) < flat_id_list_str.size()) {
                flat_id_list.push_back(stoi(flat_id_list_str.substr(0, flat_id_list_str.find(delimiter))));
                flat_id_list_str = flat_id_list_str.substr(flat_id_list_str.find(delimiter)+1);
            }
            flat_id_list.push_back(stoi(flat_id_list_str));

            // Pass vector to function
            apartmentList->relocate_flats_to_same_apartments(arguments.at(1),stoi(arguments.at(2)),flat_id_list);
            continue;
        }
        if(command=="list_apartments") {
            Node* apartmentNode = apartmentList->head;
            // If list is empty
            if(apartmentNode== nullptr) {
                outputFile << "There is no apartment" << "\n\n";
                continue;
            }

            // Traverse in apartment list
            while(apartmentNode!=apartmentList->tail) {
                outputFile << apartmentNode->apartment->name << "(" << apartmentNode->apartment->max_bandwidth << ")";
                DoubleNode* flatNode = apartmentNode->apartment->flatList->head;
                // Traverse in flat list
                while(flatNode != nullptr) {
                    outputFile << "\tFlat" << flatNode->flat->ID << "(" << flatNode->flat->initial_bandwidth << ")";
                    flatNode = flatNode->next;
                }
                apartmentNode = apartmentNode->next;
                outputFile << "\n";
            }
            // Write the tail of apartment list
            outputFile << apartmentNode->apartment->name << "(" << apartmentNode->apartment->max_bandwidth << ")";
            DoubleNode* flatNode = apartmentNode->apartment->flatList->head;
            while(flatNode != nullptr) {
                outputFile << "\tFlat" << flatNode->flat->ID << "(" << flatNode->flat->initial_bandwidth << ")";
                flatNode = flatNode->next;
            }
            outputFile << "\n\n";
            outputFile.flush(); // Empty the memory used by write operation.
            continue;
        }
    }
    inputFile.close();
    outputFile.close();
    delete apartmentList;
}
