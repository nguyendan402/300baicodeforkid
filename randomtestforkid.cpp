#include <stdio.h>

int main()
{
    int a[100], n;
    int i, j, vtMin, temp;

    // Nhap n
    printf("Nhap n = ");
    scanf("%d", &n);

    // Nhap day
    printf("Nhap day so:\n");
    for (i = 0; i < n; i++)
    {
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }

    // Sap xep chon
    for (i = 0; i < n - 1; i++)
    {
        vtMin = i;

        for (j = i + 1; j < n; j++)
        {
            if (a[j] < a[vtMin])
            {
                vtMin = j;
            }
        }

        // Doi cho
        temp = a[i];
        a[i] = a[vtMin];
        a[vtMin] = temp;
    }

    // Xuat ket qua
    printf("Day sau khi sap xep khong giam:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}