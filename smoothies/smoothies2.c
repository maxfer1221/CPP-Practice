#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item
{
    int itemID;
    int numParts;
} item;

typedef struct recipe
{
    int numItems;
    item *itemList;
    int totalParts;
} recipe;

char **readIngredients(int numIngredients);
recipe **readAllRecipes(int numRecipes);
recipe *readRecipe(int numItems);
double *calculateOrder(int numSmoothies, recipe **recipeList, int numIngredients);

int main()
{
    recipe **smoothieList;
    double *amtOfEachItem;

    int ingredientCount;
    int recipeCount;
    int storeCount;

    printf("How many ingredients will there be: ");

    scanf("%d", &ingredientCount);
    char **ingredients = readIngredients(ingredientCount);

    scanf("%d", &recipeCount);
    smoothieList = readAllRecipes(recipeCount);

    // item *itemList = (*smoothieList)->itemList;

    // for (int i = 0; i < 10; i++)
    // {
    //     printf("id: %i\n", (itemList + i)->itemID);
    //     printf("numParts: %i\n", (itemList + i)->numParts);
    // }

    scanf("%d", &storeCount);
    int numSmoothies;
    for (int i = 1; i <= storeCount; i++)
    {
        scanf("%d", &numSmoothies);
        amtOfEachItem = calculateOrder(numSmoothies, smoothieList, ingredientCount);
        // for (int i = 0; i < 10; i++)
        // {
        //     printf("id: %i\n", (itemList + i)->itemID);
        //     printf("numParts: %i\n", (itemList + i)->numParts);
        // }
        printf("Store #%i:\n", i);
        for (int j = 0; j < ingredientCount; j++)
        {
            if (amtOfEachItem[j] != 0)
            {
                printf("%s %.6lf\n", ingredients[j], amtOfEachItem[j]);
            }
        }
        free(amtOfEachItem);
    }
}

char **readIngredients(int numIngredients)
{
    char **ingredients = (char **)calloc(numIngredients, sizeof(char *));
    char buffer[21];

    for (int i = 0; i < numIngredients; i++)
    {
        printf("Ingredient number %i: ", i + 1);
        scanf("%s", buffer);
        // printf("%i", strlen(buffer));
        char *ingredient = (char *)malloc(strlen(buffer) + 1);
        strcpy(ingredient, buffer);
        *(ingredients + i) = ingredient;
        // printf("%s", ingredient);
    }

    // printf("%s", *(ingredients+1));

    return ingredients;
}

recipe **readAllRecipes(int numRecipes)
{
    recipe **smoothieList = (recipe **)calloc(numRecipes, sizeof(recipe *));
    int numIngredients;
    for (int i = 0; i < numRecipes; i++)
    {
        scanf("%d", &numIngredients);
        *(smoothieList + i) = readRecipe(numIngredients);
    }

    return smoothieList;
}

recipe *readRecipe(int numItems)
{
    recipe *finalRecipe = (recipe *)malloc(sizeof(recipe));
    item *itemList = (item *)calloc(numItems, sizeof(item));
    int totalParts = 0;
    int itemID;
    int numParts;

    printf("numitems: %i\n", numItems);

    for (int i = 0; i < numItems; i++)
    {
        printf("id: %i\n", (itemList + i)->itemID);
        printf("numParts: %i\n", (itemList + i)->numParts);
    }

    for (int i = 0; i < numItems; i++)
    {
        scanf("%d", &itemID);
        scanf("%d", &numParts);
        totalParts += numParts;
        (itemList + i)->itemID = itemID;
        (itemList + i)->numParts = numParts;
        printf("%i", (itemList + i)->numParts);
    }

    // for (int i = 0; i < 10; i++)
    // {
    //     printf("id: %i\n", (itemList + i)->itemID);
    //     printf("numParts: %i\n", (itemList + i)->numParts);
    // }

    finalRecipe->numItems = numItems;
    finalRecipe->itemList = itemList;
    finalRecipe->totalParts = totalParts;
}

double *calculateOrder(int numSmoothies, recipe **recipeList, int numIngredients)
{
    double *ingredientCounts = (double *)calloc(numIngredients, sizeof(double));
    int recipeNum;
    int weight;

    for (int i = 0; i < numSmoothies; i++)
    {
        scanf("%d", &recipeNum);
        scanf("%d", &weight);

        recipe r = **(recipeList + recipeNum);

        double totalParts = (double)(r.totalParts);
        int partsLeft = r.totalParts;

        // printf("numing: %i\n", numIngredients);

        for (int j = 0; j < numIngredients; j++)
        {
            item *itemList = r.itemList;
            // printf("%i\n", (itemList + j)->itemID);
            // printf("%i\n", (itemList + j)->numParts);
            partsLeft -= (itemList + j)->numParts;
            // printf("%s")
            int numParts = (itemList + j)->numParts;
            int itemID = (itemList + j)->itemID;
            // printf("weight: %i\n", weight);
            // printf("numParts: %i\n", numParts);
            // printf("totalParts: %lf\n", totalParts);
            // printf("%i", numParts * weight);
            // printf("ingredient count: %lf\n", numParts * weight / totalParts);
            *(ingredientCounts + itemID) += numParts * weight / totalParts;
            if (partsLeft == 0)
            {
                break;
            }
        }
        // *(ingredientCounts+i) = numParts * weight / (double)totalParts
    }

    return ingredientCounts;
}
