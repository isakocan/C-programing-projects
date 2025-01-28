#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Dosyalardan verileri y�klemek i�in fonksiyon
void load_data_from_file(const char *x_filename, const char *y_filename, double **x, double *y, int rows, int cols) {
    FILE *x_file = fopen(x_filename, "r");
    FILE *y_file = fopen(y_filename, "r");
	int i,j;
	// Dosyalar�n ba�ar�l� bir �ekilde a��l�p a��lmad���n� kontrol et
    if (!x_file || !y_file) {
        printf("Error: Unable to open file(s): %s or %s\n", x_filename, y_filename);
        exit(1);
    }

	// x dosyas�ndan x dizisine veri oku
    for ( i = 0; i < rows; i++) {
        for ( j = 0; j < cols; j++) {
            fscanf(x_file, "%lf", &x[i][j]);
        }
    }
	// y dosyas�ndan y dizisine veri oku
    for ( i = 0; i < rows; i++) {
        fscanf(y_file, "%lf", &y[i]);
    }
	// Dosyalar� kapat
    fclose(x_file);
    fclose(y_file);
}


// Bir diziyi dosyaya kaydetmek i�in fonksiyon
void save_array_to_file(const char *base_filename, double *array, double first_w_value)
{
    char filename[50];
    // Dosya ad�n� temel dosya ad� ve ilk a��rl�k de�erine g�re olu�tur
    sprintf(filename, "%s_Wfirst; %f.txt", base_filename, first_w_value);
    FILE *file = fopen(filename, "w");
    int i;
    // Diziyi dosyaya yaz
    for (i = 0; i < 301; i++)
    {
        fprintf(file, "%lf\n", array[i]);
    }
    // Dosyay� kapat
    fclose(file);
}

// Bir matrisi dosyaya kaydetmek i�in fonksiyon
void save_matrix_to_file(const char *base_filename, double **matrix, double first_w_value)
{
    char filename[50];
    // Dosya ad�n� temel dosya ad� ve ilk a��rl�k de�erine g�re olu�tur
    sprintf(filename, "%s_Wfirst; %f.txt", base_filename, first_w_value);
    FILE *file = fopen(filename, "w");
    int i, j;
    // Matrisi dosyaya yaz
    for (i = 0; i < 301; i++)
    {
        for (j = 0; j < 577; j++)
        {
            fprintf(file, "%lf ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    // Dosyay� kapat
    fclose(file);
}

// �lk a��rl�k de�erini olu�turmak i�in fonksiyon
void create_first_w(double first_value, double *w)
{
    int i;
    // �lk a��rl�k de�erlerini w dizisine ata
    for (i = 0; i < 577; i++)
    {
        w[i] = first_value;
    }
}

// Gradyan hesaplamak i�in fonksiyon
double calc_gradient(double w, double x, double y)
{
    double res = (-2) * (y - tanh(w * x)) * (1 - (tanh(w * x) * tanh(w * x))) * x;
    return res;
}

// loss hesaplamak i�in fonksiyon
double calc_loss(double *w, double **x, double *y)
{
    int i, j;
    double tanh_in = 0.0, sum = 0.0;
    // T�m �rneklerin loss de�erini hesapla ve topla
	for (i = 0; i < 160; i++)
    {
        for (j = 0; j < 577; j++)
        {
            tanh_in += w[j] * x[i][j]; // Tanjant fonksiyonunun giri� de�eri hesaplan�r.
        }

        sum += (y[i] - tanh(tanh_in)) * (y[i] - tanh(tanh_in)); // B�t�n �rnekler i�in loss de�erleri toplan�r
        tanh_in = 0.0;
    }
    sum = (double)sum / 160.0; // Ortalama loss hesaplan�r
    return sum;
}

// Do�ruluk oran�n� hesaplamak i�in fonksiyon
double calc_accur(double **x, double *y, double *w, int data_count)
{

    int correct_count = 0;
    int i, j;
    double tanh_in = 0.0, tanh_res, accuracy;
	// T�m veriler �zerinde do�ruluk oran�n� hesapla
    for (i = 0; i < data_count; i++)
    {
        for (j = 0; j < 577; j++)
        {
            tanh_in += w[j] * x[i][j]; // Tanjant fonksiyonunun giri� de�eri hesaplan�r.
        }
        tanh_res = tanh(tanh_in);
        // Do�ru tahminleri say
        if (tanh_res >= 0.1 && tanh_res <= 1 && y[i] == 1 || tanh_res <= -0.1 && tanh_res >= -1 && y[i] == -1)
        {
            correct_count++;
        }
        tanh_in = 0.0;
    }
	// Do�ruluk oran�n� hesapla
    accuracy = (double)correct_count / data_count;
    return accuracy * 100;
}

// Gradient Descent (GD) algoritmas�n� ger�ekle�tiren fonksiyon
void gradient_descent(float learning_rate, double **x, double *y, double first_w_value, double **x_test, double *y_test)
{
    double *w = (double *)malloc(577 * sizeof(double));
    // �lk w de�erleri matrise aktar�l�yor
    create_first_w(first_w_value, w);
    //Sat�r say�s�: 300 iterasyon + ba�lang�� w de�erleri
    double *loss = (double *)malloc(301 * sizeof(double));
    double *time_matrix = (double *)malloc(301 * sizeof(double));
    double *accur = (double *)malloc(301 * sizeof(double));
    double *accur_test = (double *)malloc(301 * sizeof(double));
    time_t start, end;
    int iter, i, j;
    double sum_of_gradients = 0.0;
    double **w_tsne = (double **)malloc(301 * sizeof(double *)); 
    for (i = 0; i < 301; i++)
    {
        w_tsne[i] = (double *)malloc(577 * sizeof(double));
    }
    // �lk w de�erleri ilk sat�ra atan�yor
    create_first_w(first_w_value, w_tsne[0]);
    loss[0] = calc_loss(w, x, y);
    time_matrix[0] = 0;
    accur[0] = calc_accur(x, y, w, 160);
    accur_test[0] = calc_accur(x_test, y_test, w, 40);
    // 300 iterasyon ger�ekle�tirilir
    for (iter = 0; iter < 300; iter++)
    {

        start = clock();

        // w'nun d�ng�s�
        for (i = 0; i < 577; i++)
        {
            // �rneklerin d�ng�s�
            for (j = 0; j < 160; j++)
            {
                // Her bir x[i] i�in 160 �rnek �zerinden gradyan hesaplan�r
                sum_of_gradients += calc_gradient(w[i], x[j][i], y[j]);
            }
            // 160'a b�lerek ortalama gradyan hesaplan�r
            sum_of_gradients = (double)sum_of_gradients / 160.0;
            // Yeni w de�eri hesaplan�r
            w[i] = w[i] - (learning_rate * sum_of_gradients);
            // Yeni w de�eri kaydedilir
            w_tsne[iter + 1][i] = w[i];
            // Gradyanlar�n toplam� s�f�rlan�r.
            sum_of_gradients = 0.0;
        }

        // Bu iterasyondaki loss fonksiyon de�eri, s�re ve do�ruluk oranlar� hesaplan�r ve kaydedilir
        loss[iter + 1] = calc_loss(w, x, y);
        end = clock();
        time_matrix[iter + 1] = time_matrix[iter] + ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
        accur[iter + 1] = calc_accur(x, y, w, 160);
        accur_test[iter + 1] = calc_accur(x_test, y_test, w, 40);
    }
    
	// Sonu�lar dosyaya kaydedilir
    save_array_to_file("Gradient_Descent_Loss", loss, first_w_value);
    save_array_to_file("Gradient_Descent_Time", time_matrix, first_w_value);
    save_array_to_file("Gradient_Descent_Accuracy", accur, first_w_value);
    save_array_to_file("Gradient_Descent_Test_Accuracy", accur_test, first_w_value);
    save_matrix_to_file("Gradient_Descent_Wtsne", w_tsne, first_w_value);
    
    // Bellek serbest b�rak�l�r
    free(w);
    free(loss);
    free(time_matrix);
    free(accur);
    free(accur_test);
    for (i = 0; i < 301; i++)
    {
        free(w_tsne[i]);
    }
    free(w_tsne);
}

// Stochastic Gradient Descent (SGD) algoritmas�n� ger�ekle�tiren fonksiyon
void stochastic_gradient_descent(double learning_rate, double **x, double *y, double first_w_value, double **x_test, double *y_test)
{

    double *w, gradient = 0.0;
    w = (double *)malloc(577 * sizeof(double));
    // �lk w de�erleri matrise aktar�l�yor
    create_first_w(first_w_value, w);
    //Sat�r say�s�: 300 iterasyon + ba�lang�� w de�erleri
    double *loss = (double *)malloc(301 * sizeof(double));
    double *time_matrix = (double *)malloc(301 * sizeof(double));
    double *accur = (double *)malloc(301 * sizeof(double));
    double *accur_test = (double *)malloc(301 * sizeof(double));
    time_t start, end;
    int iter, i, j;
    double **w_tsne = (double **)malloc(301 * sizeof(double *));
    for (i = 0; i < 301; i++)
    {
        w_tsne[i] = (double *)malloc(577 * sizeof(double));
    }
    // �lk w de�erleri ilk sat�ra atan�yor
    create_first_w(first_w_value, w_tsne[0]); 
    loss[0] = calc_loss(w, x, y);
    time_matrix[0] = 0;
    accur[0] = calc_accur(x, y, w, 160);
    accur_test[0] = calc_accur(x_test, y_test, w, 40);
	srand(time(NULL));
    // 300 iterasyon ger�ekle�tirilir
    for (iter = 0; iter < 300; iter++)
    {

        start = clock();
        j = rand() % 160; // Rastgele bir �rnek se�ilir

        // w'nun d�ng�s�
        for (i = 0; i < 577; i++)
        {
            // Rastgele bir �rnek i�in gradyan hesaplan�r
            gradient = calc_gradient(w[i], x[j][i], y[j]);
            // Yeni w de�eri hesaplan�r
            w[i] = w[i] - (learning_rate * gradient);

            // Yeni w de�eri kaydedilir
            w_tsne[iter + 1][i] = w[i];
        }

        // Bu iterasyondaki loss fonksiyon de�eri, s�re ve do�ruluk oranlar� hesaplan�r ve kaydedilir
        loss[iter + 1] = calc_loss(w, x, y);
        end = clock();
        time_matrix[iter + 1] = time_matrix[iter] + ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
        accur[iter + 1] = calc_accur(x, y, w, 160);
        accur_test[iter + 1] = calc_accur(x_test, y_test, w, 40);
    }

	// Sonu�lar dosyaya kaydedilir
    save_array_to_file("Stochastic_Gradient_Descent_Loss", loss, first_w_value);
    save_array_to_file("Stochastic_Gradient_Descent_Time", time_matrix, first_w_value);
    save_array_to_file("Stochastic_Gradient_Descent_Accuracy", accur, first_w_value);
    save_array_to_file("Stochastic_Gradient_Descent_Test_Accuracy", accur_test, first_w_value);
    save_matrix_to_file("Stochastic_Gradient_Descent_Wtsne", w_tsne, first_w_value);
    
	// Bellek serbest b�rak�l�r
	free(w);
    free(loss);
    free(time_matrix);
    free(accur);
    free(accur_test);
    for (i = 0; i < 301; i++)
    {
        free(w_tsne[i]);
    }
    free(w_tsne);
}


// ADAM optimizasyon algoritmas�n� ger�ekle�tiren fonksiyon
void ADAM(double learning_rate, double **x, double *y, double first_w_value, double **x_test, double *y_test)
{
    double *w = (double *)malloc(577 * sizeof(double));
    // �lk w de�erleri matrise aktar�l�yor
    create_first_w(first_w_value, w);
    //Sat�r say�s�: 300 iterasyon + ba�lang�� w de�erleri
    double *loss = (double *)malloc(301 * sizeof(double));
    double *time_matrix = (double *)malloc(301 * sizeof(double));
    double *accur = (double *)malloc(301 * sizeof(double));
    double *accur_test = (double *)malloc(301 * sizeof(double));
    time_t start, end;
    int iter, i, j;
    double *mt = (double*)malloc(577*sizeof(double));
    double *vt = (double*)malloc(577*sizeof(double));
    create_first_w(0, mt);
    create_first_w(0, vt);
    double mt_hat, vt_hat, gradient = 0.0, epsilon = 0.00000001, beta1 = 0.9, beta2 = 0.999;
    double **w_tsne = (double **)malloc(301 * sizeof(double *));
    for (i = 0; i < 301; i++)
    {
        w_tsne[i] = (double *)malloc(577 * sizeof(double));
    }
    // �lk w de�erleri ilk sat�ra atan�yor
    create_first_w(first_w_value, w_tsne[0]); 
    loss[0] = calc_loss(w, x, y);
    time_matrix[0] = 0;
    accur[0] = calc_accur(x, y, w, 160);
    accur_test[0] = calc_accur(x_test, y_test, w, 40);
	srand(time(NULL));
	
    // 300 iterasyon ger�ekle�tirilir
    for (iter = 0; iter < 300; iter++)
    {

        start = clock();
        j = rand() % 160; // Rastgele bir �rnek se�ilir
        
        // w'nun d�ng�s�
        for (i = 0; i < 577; i++)
        {
            
            // Rastgele bir �rnek i�in gradyan, mt ve vt de�erleri bulunur
            gradient = calc_gradient(w[i], x[j][i], y[j]);
            mt[i] = beta1 * mt[i] + (1.0 - beta1) * gradient;
            vt[i] = beta2 * vt[i] + (1.0 - beta2) * gradient * gradient;
            mt_hat = (double) mt[i] / (1.0 - pow(beta1, (iter+1)));
            vt_hat = (double) vt[i] / (1.0 - pow(beta2, (iter+1)));
            // ADAM algoritmas�na g�re yeni w de�eri hesaplan�r
            w[i] = w[i] - (learning_rate * mt_hat / (sqrt(vt_hat) + epsilon));
            // Yeni w de�eri kaydedilir
            w_tsne[iter + 1][i] = w[i];
        }

        // Bu iterasyondaki loss fonksiyon de�eri, s�re ve do�ruluk oranlar� hesaplan�r ve kaydedilir
        loss[iter + 1] = calc_loss(w, x, y);
        end = clock();
        time_matrix[iter + 1] = time_matrix[iter] + ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
        accur[iter + 1] = calc_accur(x, y, w, 160);
        accur_test[iter + 1] = calc_accur(x_test, y_test, w, 40);
    }

	// Sonu�lar dosyaya kaydedilir
    save_array_to_file("ADAM_Loss", loss, first_w_value);
    save_array_to_file("ADAM_Time", time_matrix, first_w_value);
    save_array_to_file("ADAM_Accuracy", accur, first_w_value);
    save_array_to_file("ADAM_Test_Accuracy", accur_test, first_w_value);
    save_matrix_to_file("ADAM_Wtsne", w_tsne, first_w_value);
    
    // Bellek serbest b�rak�l�r
    free(w);
    free(loss);
    free(time_matrix);
    free(accur);
    free(accur_test);
    free(mt);
    free(vt);
    for (i = 0; i < 301; i++)
    {
        free(w_tsne[i]);
    }
    free(w_tsne);
}

int main()
{
    // B�t�n y�ntemler i�in ayn� olan veriler main fonksiyonda olu�turuluyor
    double learning_rate = 0.001;
    double *y = (double *)malloc(160 * sizeof(double));
    double *y_test = (double *)malloc(40 * sizeof(double));
    double **x = (double **)malloc(160 * sizeof(double *));
    double **x_test = (double **)malloc(40 * sizeof(double *));
    int i, j;
    for (i = 0; i < 160; i++)
    {
        if (i < 40)
            x_test[i] = (double *)malloc(577 * sizeof(double));
        x[i] = (double *)malloc(577 * sizeof(double));
    }

	// Veriler dosyalardan y�klenir
	load_data_from_file("x.txt", "y.txt", x, y, 160, 577);
    load_data_from_file("x_test.txt", "y_test.txt", x_test, y_test, 40, 577);

    printf("Data loaded successfully.\n");

    // w ba�lang�� de�eri 0 olursa
    gradient_descent(learning_rate, x, y, 0.0, x_test, y_test);
    stochastic_gradient_descent(learning_rate, x, y, 0.0, x_test, y_test);
    ADAM(learning_rate, x, y, 0.0, x_test, y_test);
    
    // w ba�lang�� de�eri 0.1 olursa
    gradient_descent(learning_rate, x, y, 0.1, x_test, y_test);
    stochastic_gradient_descent(learning_rate, x, y, 0.1, x_test, y_test);
    ADAM(learning_rate, x, y, 0.1, x_test, y_test);
    
    // w ba�lang�� de�eri 0.01 olursa
    gradient_descent(learning_rate, x, y, 0.01, x_test, y_test);
    stochastic_gradient_descent(learning_rate, x, y, 0.01, x_test, y_test);
    ADAM(learning_rate, x, y, 0.01, x_test, y_test);
    
    // w ba�lang�� de�eri 0.001 olursa
    gradient_descent(learning_rate, x, y, 0.001, x_test, y_test);
    stochastic_gradient_descent(learning_rate, x, y, 0.001, x_test, y_test);
    ADAM(learning_rate, x, y, 0.001, x_test, y_test);
    
    // w ba�lang�� de�eri 0.0001 olursa
    gradient_descent(learning_rate, x, y, 0.0001, x_test, y_test);
    stochastic_gradient_descent(learning_rate, x, y, 0.0001, x_test, y_test);
    ADAM(learning_rate, x, y, 0.0001, x_test, y_test);
	
	printf("\nFiles saved successfully.");
	
	// Bellek serbest b�rak�l�r
    free(y);
    free(y_test);
    for (i = 0; i < 160; i++)
    {
        free(x[i]);
        if (i < 40)
            free(x_test[i]);
    }
    free(x);
    free(x_test);
    
	return 0;
}
