#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct course
{
    int num;
    char *subject;
    struct course *prev;
    struct course *next;
} course;

course *getnode(char *str, int num)
{
    course *newnode = (course *)malloc(sizeof(course));
    newnode->subject = strdup(str);
    newnode->num = num;
    newnode->prev = NULL;
    newnode->next = NULL;
    return newnode;
}

course *create(int *num, int *next, int *prev, char *str[], course *head, int how_many)
{

    int flag = 0;

    for (int i = 0; i < how_many; i++)
    {
        if (prev[i] == -1)
        {
            head = getnode(str[i], i);
            flag = i;
        }
    }
    course *temp = head;

    for (int i = 0; i < how_many; i++)
    {
        int exist = 0;

        for (int j = 0; j < how_many; j++)
        {
            course *temp3 = head;
            course *temp4;

            while (temp3->next != NULL)
            { // create tail

                temp3 = temp3->next;
                if (temp->next == NULL)
                {
                    temp4 = temp3;
                }
            }

            if (next[flag] == num[j])
            {
                while (temp3 != NULL)
                {
                    if (temp3->num == j)
                    { // seeee whether head have the node
                        exist = 1;
                        break;
                    }
                    temp3 = temp3->next;
                }
                if (exist == 1)
                {
                    temp->next = temp3;
                }
                else if (exist == 0)
                {
                    temp->next = getnode(str[j], j); // scribe the have already created node
                    temp = temp->next;
                }
            }

            if (prev[flag] == num[j])
            {
                while (temp4 != NULL)
                {
                    if (temp4->num == j)
                    { // seeee whether head have the node
                        break;
                    }
                    temp4 = temp4->prev;
                }
                temp->prev = temp4;
            }
        }
    }
    return head;
}

int main(int argc, char *argv[])
{
    int num1[1000], num2[1000], num3[1000];
    char **str;

    str = (char **)malloc(sizeof(char *) * 100);
    for (int i = 0; i < 100; i++)
    {
        str[i] = (char *)malloc(100 * sizeof(char));
    }

    course *head = NULL;
    int k = 0;
    int times = 0;
    scanf("%d", &times);
    while (times--)
    {
        scanf("%d %d %d %s", &num1[k], &num2[k], &num3[k], str[k]);

        k++;
    }

    head = create(num1, num2, num3, str, head, k);

    course *temp = head;

    char action;

    printf("Current Course: %s\n", temp->subject);
    while (scanf(" %c", &action) && action != 'q')
    {
        if (action == 'n')
        {
            if (temp->next != NULL)
            {
                temp = temp->next;
            }
            else
            {
                printf("There is no next course.\n");
            }
        }
        else if (action == 'p')
        {
            if (temp->prev != NULL)
            {
                temp = temp->prev;
            }
            else
            {
                printf("There is no previous course.\n");
            }
        }
        printf("Current Course: %s\n", temp->subject);
    }
    return 0;
}