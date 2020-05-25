#include "Turing.h"
#include <iostream>

Turing::Turing()
{
	tape[5] = "beta";
	tape[4] = "1";
	tape[3] = "1";
	tape[2] = "1";
	tape[1] = "1";

	state = 3;
	head = 5;
    step = 0;

    print();
}

void Turing::print()
{
    std::cout << "step: " << step << std::endl;
    for (std::map<int, std::string>::iterator it = tape.begin(); it != tape.end(); ++it)
    {
        std::cout << it->second << " ";
    }
    std::cout << std::endl << std::endl;
}

void Turing::run()
{
    ++step;

    #pragma region state1
    if (state == 1 && tape[head] == "lambda")
    {
        state = 5;
        tape[head] = "alpha";
        ++head;
        print();
        run();
        return;
    }

    if (state == 1 && tape[head] == "1")
    {
        state = 5;
        tape[head] = "beta";
        print();
        run();
        return;
    }

    if (state == 1 && tape[head] == "alpha")
    {
        state = 4;
        tape[head] = "1";
        --head;
        print();
        run();
        return;
    }

    if (state == 1 && tape[head] == "beta")
    {
        state = 4;
        tape[head] = "1";
        ++head;
        print();
        run();
        return;
    }
    #pragma endregion

    #pragma region state2
    if (state == 2)
    {
        print();
        return;
    }
    #pragma endregion

    #pragma region state3
    if (state == 3 && tape[head] == "lambda")
    {
        state = 1;
        tape[head] = "1";
        ++head;
        print();
        run();
        return;
    }

    if (state == 3 && tape[head] == "1")
    {
        state = 2;
        tape[head] = "alpha";
        --head;
        print();
        run();
        return;
    }

    if (state == 3 && tape[head] == "alpha")
    {
        state = 5;
        tape[head] = "beta";
        ++head;
        print();
        run();
        return;
    }

    if (state == 3 && tape[head] == "beta")
    {
        state = 1;
        tape[head] = "1";
        --head;
        print();
        run();
        return;
    }
    #pragma endregion

    #pragma region state4
    if (state == 4 && tape[head] == "lambda")
    {
        state = 3;
        tape[head] = "beta";
        print();
        run();
        return;
    }

    if (state == 4 && tape[head] == "1")
    {
        state = 2;
        tape[head] = "alpha";
        ++head;
        print();
        run();
        return;
    }

    if (state == 4 && tape[head] == "alpha")
    {
        state = 5;
        tape[head] = "alpha";
        --head;
        print();
        run();
        return;
    }

    if (state == 4 && tape[head] == "beta")
    {
        state = 3;
        tape[head] = "1";
        --head;
        print();
        run();
        return;
    }
    #pragma endregion

    #pragma region state5
    if (state == 5 && tape[head] == "lambda")
    {
        state = 2;
        tape[head] = "alpha";
        ++head;
        print();
        run();
        return;
    }

    if (state == 5 && tape[head] == "1")
    {
        state = 1;
        tape[head] = "beta";
        --head;
        print();
        run();
        return;
    }

    if (state == 5 && tape[head] == "alpha")
    {
        state = 4;
        tape[head] = "1";
        print();
        run();
        return;
    }

    if (state == 5 && tape[head] == "beta")
    {
        state = 3;
        tape[head] = "lambda";
        print();
        run();
        return;
    }
    #pragma endregion
}