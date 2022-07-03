#include <cs50.h>
#include <stdio.h>

long read_card_number(void);
int verify_cardnum_size(long card_number_temp);
int verify_initial_13dig(long card_number_temp);
int verify_initial_amex(long card_number_temp);
int verify_initial_16dig(long card_number_temp);
int verify_cardnum_initial(void);
long lastnum_assign(long full);
long rm_lastnumber(long total);
int unmult_sum(void);
int separateandsum(int doub_total);
int doub_sum(void);
int checksum(void);

int unmult;
int doub;
int card_size;
long card_number;
long card_number_test;

int main(void)
{
    card_number = read_card_number();
    // printf("%ld\n",card_number);

    while (true)
    {
        card_size = verify_cardnum_size(card_number);
        // printf("%i\n",card_size);

        if (card_size == 0)
        {
            printf("INVALID\n");
            break;
        }

        int card_flag = verify_cardnum_initial();
        if (card_flag == 0)
        {
            printf("INVALID\n");
            break;
        }
        //printf("%i\n",card_flag);

        card_number_test = card_number;

        // printf("%i\n",checksum());

        int mod_checksum = checksum();
        if (mod_checksum != 0)
        {
            printf("INVALID\n");
            break;
        }
        else
        {
            switch (card_flag)
            {
                case 1:
                {
                    printf("VISA\n");
                    break;
                }
                case 2:
                {
                    printf("AMEX\n");
                    break;
                }
                case 3:
                {
                    printf("MASTERCARD\n");
                    break;
                }
            }
            break;
        }
    }


}







// routine of the checksum

long lastnum_assign(long full)
{
    return full % 10;
}

long rm_lastnumber(long total)
{
    // printf("lastnumas: %ld total:%ld \n",lastnum_assign(total),total);
    return (((total - lastnum_assign(total)) / 10)); // returns the total subtracted per the last number of the total and divided per 10
}
// to call for card total: rm_lastnumber(card_number_test)


int unmult_sum(void) // function that makes the separation and the sum of the non multiplied numbers from the algorithm
{
    return unmult + lastnum_assign(card_number_test);
}

int separateandsum(int doub_total) // function that separates the digits and sum them
{
    int lastnum_doub = lastnum_assign(doub_total); // assign the last digit of the double total
    int first_total = rm_lastnumber(doub_total); // assign the first digit of the double total
    return first_total + lastnum_doub; // sums the first and the last digit and returns to the caller
}

int doub_sum(void) // function that makes the separation and the sum of the doubled numbers from the algorithm
{
    int doub_temp = lastnum_assign(card_number_test) * 2;
    if (doub_temp >= 10)
    {
        return doub + separateandsum(doub_temp);
    }
    else
    {
        return doub + doub_temp;
    }
}

// end routine




// function that verify if the card number size is valid and returns 0 if is invalid, or returns the card_size if is valid

int verify_cardnum_size(long card_number_temp)
{
    int card_size_temp = 0;
    do
    {
        card_number_temp = card_number_temp / 10;
        // divides the card number per 10 until card number being 0, and for every division adds 1 in counter of card size
        card_size_temp = card_size_temp + 1;
    }
    while (card_number_temp >= 1);

    if (card_size_temp < 13 || card_size_temp > 16)
    {
        return 0;
    }
    else
    {
        return card_size_temp;
    }
}

// end function




long read_card_number(void) //function that reads the card number and return to the variable
{
    return get_long("Number: ");
}




// functions to verify if the first digits are valid
//return card_verify values declararation
//0:invalid
//1:visa
//2:amex
//3:mastercard

int verify_initial_13dig(long card_number_temp)
{
    int card_initial = card_number_temp / (10e11);
    // printf("%i\n",card_initial);
    return 1;
}

int verify_initial_amex(long card_number_temp)
{
    int card_initial = card_number_temp / (10e12);
    // printf("%i\n",card_initial);
    if (card_initial == 34 || card_initial == 37)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

int verify_initial_16dig(long card_number_temp)
{
    int card_initial = card_number_temp / (10e13);
    // printf("%i\n",card_initial);
    if (card_initial == 51 || card_initial == 52 || card_initial == 53 || card_initial == 54 || card_initial == 55)
    {
        return 3;
    }
    else
    {
        card_initial = card_initial / 10;
    }
    if (card_initial == 4)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int verify_cardnum_initial(void)
{
    if (card_size == 13)
    {
        if (verify_initial_13dig(card_number) == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (card_size == 15)
    {
        if (verify_initial_amex(card_number) == 2)
        {
            return 2;
        }
        else
        {
            return 0;
        }

    }
    else if (card_size == 16)
    {
        if (verify_initial_16dig(card_number) == 1)
        {
            return 1;
        }
        else if (verify_initial_16dig(card_number) == 3)
        {
            return 3;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

// end routine

int checksum(void)
{
    do
    {
        unmult = unmult_sum();
        card_number_test = rm_lastnumber(card_number_test);
        doub = doub_sum();
        card_number_test = rm_lastnumber(card_number_test);
        // printf("%ld\n",card_number_test);
    }
    while (card_number_test > 1);

    int checksum_var = unmult + doub;
    checksum_var = checksum_var %  10;
    return checksum_var;
}