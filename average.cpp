#include<iostream>
#include<cstring>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please input numbers to find average." << endl;
        return 0;
    }

    int count = argc - 1;
    double sum = 0;

    for (int i = 1; i < argc; i++) {
        sum += atof(argv[i]);
    }

    double avg = sum / count;

    cout << "---------------------------------" << endl;
    cout << "Average of " << count << " numbers = " << avg << endl;
    cout << "---------------------------------" << endl;

    return 0;
}
