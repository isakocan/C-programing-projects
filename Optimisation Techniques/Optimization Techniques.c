#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Dosyalardan verileri yüklemek için fonksiyon
void load_data_from_file(const char *x_filename, const char *y_filename, double **x, double *y, int rows, int cols) {
    FILE *x_file = fopen(x_filename, "r");
    FILE *y_file = fopen(y_filename, "r");
	int i,j;
	// Dosyalarýn baþarýlý bir þekilde açýlýp açýlmadýðýný kontrol et
    if (!x_file || !y_file) {
        printf("Error: Unable to open file(s): %s or %s\n", x_filename, y_filename);
        exit(1);
    }

	// x dosyasýndan x dizisine veri oku
    for ( i = 0; i < rows; i++) {
        for ( j = 0; j < cols; j++) {
            fscanf(x_file, "%lf", &x[i][j]);
        }
    }
	// y dosyasýndan y dizisine veri oku
    for ( i = 0; i < rows; i++) {
        fscanf(y_file, "%lf", &y[i]);
    }
	// Dosyalarý kapat
    fclose(x_file);
    fclose(y_file);
}


// Bir diziyi dosyaya kaydetmek için fonksiyon
void save_array_to_file(const char *base_filename, double *array, double first_w_value)
{
    char filename[50];
    // Dosya adýný temel dosya adý ve ilk aðýrlýk deðerine göre oluþtur
    sprintf(filename, "%s_Wfirst; %f.txt", base_filename, first_w_value);
    FILE *file = fopen(filename, "w");
    int i;
    // Diziyi dosyaya yaz
    for (i = 0; i < 301; i++)
    {
        fprintf(file, "%lf\n", array[i]);
    }
    // Dosyayý kapat
    fclose(file);
}

// Bir matrisi dosyaya kaydetmek için fonksiyon
void save_matrix_to_file(const char *base_filename, double **matrix, double first_w_value)
{
    char filename[50];
    // Dosya adýný temel dosya adý ve ilk aðýrlýk deðerine göre oluþtur
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
    // Dosyayý kapat
    fclose(file);
}

// Ýlk aðýrlýk deðerini oluþturmak için fonksiyon
void create_first_w(double first_value, double *w)
{
    int i;
    // Ýlk aðýrlýk deðerlerini w dizisine ata
    for (i = 0; i < 577; i++)
    {
        w[i] = first_value;
    }
}

// Gradyan hesaplamak için fonksiyon
double calc_gradient(double w, double x, double y)
{
    double res = (-2) * (y - tanh(w * x)) * (1 - (tanh(w * x) * tanh(w * x))) * x;
    return res;
}

// loss hesaplamak için fonksiyon
double calc_loss(double *w, double **x, double *y)
{
    int i, j;
    double tanh_in = 0.0, sum = 0.0;
    // Tüm örneklerin loss deðerini hesapla ve topla
	for (i = 0; i < 160; i++)
    {
        for (j = 0; j < 577; j++)
        {
            tanh_in += w[j] * x[i][j]; // Tanjant fonksiyonunun giriþ deðeri hesaplanýr.
        }

        sum += (y[i] - tanh(tanh_in)) * (y[i] - tanh(tanh_in)); // Bütün örnekler için loss deðerleri toplanýr
        tanh_in = 0.0;
    }
    sum = (double)sum / 160.0; // Ortalama loss hesaplanýr
    return sum;
}

// Doðruluk oranýný hesaplamak için fonksiyon
double calc_accur(double **x, double *y, double *w, int data_count)
{

    int correct_count = 0;
    int i, j;
    double tanh_in = 0.0, tanh_res, accuracy;
	// Tüm veriler üzerinde doðruluk oranýný hesapla
    for (i = 0; i < data_count; i++)
    {
        for (j = 0; j < 577; j++)
        {
            tanh_in += w[j] * x[i][j]; // Tanjant fonksiyonunun giriþ deðeri hesaplanýr.
        }
        tanh_res = tanh(tanh_in);
        // Doðru tahminleri say
        if (tanh_res >= 0.1 && tanh_res <= 1 && y[i] == 1 || tanh_res <= -0.1 && tanh_res >= -1 && y[i] == -1)
        {
            correct_count++;
        }
        tanh_in = 0.0;
    }
	// Doðruluk oranýný hesapla
    accuracy = (double)correct_count / data_count;
    return accuracy * 100;
}

// Gradient Descent (GD) algoritmasýný gerçekleþtiren fonksiyon
void gradient_descent(float learning_rate, double **x, double *y, double first_w_value, double **x_test, double *y_test)
{
    double *w = (double *)malloc(577 * sizeof(double));
    // Ýlk w deðerleri matrise aktarýlýyor
    create_first_w(first_w_value, w);
    //Satýr sayýsý: 300 iterasyon + baþlangýç w deðerleri
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
    // Ýlk w deðerleri ilk satýra atanýyor
    create_first_w(first_w_value, w_tsne[0]);
    loss[0] = calc_loss(w, x, y);
    time_matrix[0] = 0;
    accur[0] = calc_accur(x, y, w, 160);
    accur_test[0] = calc_accur(x_test, y_test, w, 40);
    // 300 iterasyon gerçekleþtirilir
    for (iter = 0; iter < 300; iter++)
    {

        start = clock();

        // w'nun döngüsü
        for (i = 0; i < 577; i++)
        {
            // Örneklerin döngüsü
            for (j = 0; j < 160; j++)
            {
                // Her bir x[i] için 160 örnek üzerinden gradyan hesaplanýr
                sum_of_gradients += calc_gradient(w[i], x[j][i], y[j]);
            }
            // 160'a bölerek ortalama gradyan hesaplanýr
            sum_of_gradients = (double)sum_of_gradients / 160.0;
            // Yeni w deðeri hesaplanýr
            w[i] = w[i] - (learning_rate * sum_of_gradients);
            // Yeni w deðeri kaydedilir
            w_tsne[iter + 1][i] = w[i];
            // Gradyanlarýn toplamý sýfýrlanýr.
            sum_of_gradients = 0.0;
        }

        // Bu iterasyondaki loss fonksiyon deðeri, süre ve doðruluk oranlarý hesaplanýr ve kaydedilir
        loss[iter + 1] = calc_loss(w, x, y);
        end = clock();
        time_matrix[iter + 1] = time_matrix[iter] + ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
        accur[iter + 1] = calc_accur(x, y, w, 160);
        accur_test[iter + 1] = calc_accur(x_test, y_test, w, 40);
    }
    
	// Sonuçlar dosyaya kaydedilir
    save_array_to_file("Gradient_Descent_Loss", loss, first_w_value);
    save_array_to_file("Gradient_Descent_Time", time_matrix, first_w_value);
    save_array_to_file("Gradient_Descent_Accuracy", accur, first_w_value);
    save_array_to_file("Gradient_Descent_Test_Accuracy", accur_test, first_w_value);
    save_matrix_to_file("Gradient_Descent_Wtsne", w_tsne, first_w_value);
    
    // Bellek serbest býrakýlýr
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

// Stochastic Gradient Descent (SGD) algoritmasýný gerçekleþtiren fonksiyon
void stochastic_gradient_descent(double learning_rate, double **x, double *y, double first_w_value, double **x_test, double *y_test)
{

    double *w, gradient = 0.0;
    w = (double *)malloc(577 * sizeof(double));
    // Ýlk w deðerleri matrise aktarýlýyor
    create_first_w(first_w_value, w);
    //Satýr sayýsý: 300 iterasyon + baþlangýç w deðerleri
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
    // Ýlk w deðerleri ilk satýra atanýyor
    create_first_w(first_w_value, w_tsne[0]); 
    loss[0] = calc_loss(w, x, y);
    time_matrix[0] = 0;
    accur[0] = calc_accur(x, y, w, 160);
    accur_test[0] = calc_accur(x_test, y_test, w, 40);
	srand(time(NULL));
    // 300 iterasyon gerçekleþtirilir
    for (iter = 0; iter < 300; iter++)
    {

        start = clock();
        j = rand() % 160; // Rastgele bir örnek seçilir

        // w'nun döngüsü
        for (i = 0; i < 577; i++)
        {
            // Rastgele bir örnek için gradyan hesaplanýr
            gradient = calc_gradient(w[i], x[j][i], y[j]);
            // Yeni w deðeri hesaplanýr
            w[i] = w[i] - (learning_rate * gradient);

            // Yeni w deðeri kaydedilir
            w_tsne[iter + 1][i] = w[i];
        }

        // Bu iterasyondaki loss fonksiyon deðeri, süre ve doðruluk oranlarý hesaplanýr ve kaydedilir
        loss[iter + 1] = calc_loss(w, x, y);
        end = clock();
        time_matrix[iter + 1] = time_matrix[iter] + ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
        accur[iter + 1] = calc_accur(x, y, w, 160);
        accur_test[iter + 1] = calc_accur(x_test, y_test, w, 40);
    }

	// Sonuçlar dosyaya kaydedilir
    save_array_to_file("Stochastic_Gradient_Descent_Loss", loss, first_w_value);
    save_array_to_file("Stochastic_Gradient_Descent_Time", time_matrix, first_w_value);
    save_array_to_file("Stochastic_Gradient_Descent_Accuracy", accur, first_w_value);
    save_array_to_file("Stochastic_Gradient_Descent_Test_Accuracy", accur_test, first_w_value);
    save_matrix_to_file("Stochastic_Gradient_Descent_Wtsne", w_tsne, first_w_value);
    
	// Bellek serbest býrakýlýr
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


// ADAM optimizasyon algoritmasýný gerçekleþtiren fonksiyon
void ADAM(double learning_rate, double **x, double *y, double first_w_value, double **x_test, double *y_test)
{
    double *w = (double *)malloc(577 * sizeof(double));
    // Ýlk w deðerleri matrise aktarýlýyor
    create_first_w(first_w_value, w);
    //Satýr sayýsý: 300 iterasyon + baþlangýç w deðerleri
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
    // Ýlk w deðerleri ilk satýra atanýyor
    create_first_w(first_w_value, w_tsne[0]); 
    loss[0] = calc_loss(w, x, y);
    time_matrix[0] = 0;
    accur[0] = calc_accur(x, y, w, 160);
    accur_test[0] = calc_accur(x_test, y_test, w, 40);
	srand(time(NULL));
	
    // 300 iterasyon gerçekleþtirilir
    for (iter = 0; iter < 300; iter++)
    {

        start = clock();
        j = rand() % 160; // Rastgele bir örnek seçilir
        
        // w'nun döngüsü
        for (i = 0; i < 577; i++)
        {
            
            // Rastgele bir örnek için gradyan, mt ve vt deðerleri bulunur
            gradient = calc_gradient(w[i], x[j][i], y[j]);
            mt[i] = beta1 * mt[i] + (1.0 - beta1) * gradient;
            vt[i] = beta2 * vt[i] + (1.0 - beta2) * gradient * gradient;
            mt_hat = (double) mt[i] / (1.0 - pow(beta1, (iter+1)));
            vt_hat = (double) vt[i] / (1.0 - pow(beta2, (iter+1)));
            // ADAM algoritmasýna göre yeni w deðeri hesaplanýr
            w[i] = w[i] - (learning_rate * mt_hat / (sqrt(vt_hat) + epsilon));
            // Yeni w deðeri kaydedilir
            w_tsne[iter + 1][i] = w[i];
        }

        // Bu iterasyondaki loss fonksiyon deðeri, süre ve doðruluk oranlarý hesaplanýr ve kaydedilir
        loss[iter + 1] = calc_loss(w, x, y);
        end = clock();
        time_matrix[iter + 1] = time_matrix[iter] + ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
        accur[iter + 1] = calc_accur(x, y, w, 160);
        accur_test[iter + 1] = calc_accur(x_test, y_test, w, 40);
    }

	// Sonuçlar dosyaya kaydedilir
    save_array_to_file("ADAM_Loss", loss, first_w_value);
    save_array_to_file("ADAM_Time", time_matrix, first_w_value);
    save_array_to_file("ADAM_Accuracy", accur, first_w_value);
    save_array_to_file("ADAM_Test_Accuracy", accur_test, first_w_value);
    save_matrix_to_file("ADAM_Wtsne", w_tsne, first_w_value);
    
    // Bellek serbest býrakýlýr
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
    // Bütün yöntemler için ayný olan veriler main fonksiyonda oluþturuluyor
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

	// Veriler dosyalardan yüklenir
	load_data_from_file("x.txt", "y.txt", x, y, 160, 577);
    load_data_from_file("x_test.txt", "y_test.txt", x_test, y_test, 40, 577);

    printf("Data loaded successfully.\n");

    // w baþlangýç deðeri 0 olursa
    gradient_descent(learning_rate, x, y, 0.0, x_test, y_test);
    stochastic_gradient_descent(learning_rate, x, y, 0.0, x_test, y_test);
    ADAM(learning_rate, x, y, 0.0, x_test, y_test);
    
    // w baþlangýç deðeri 0.1 olursa
    gradient_descent(learning_rate, x, y, 0.1, x_test, y_test);
    stochastic_gradient_descent(learning_rate, x, y, 0.1, x_test, y_test);
    ADAM(learning_rate, x, y, 0.1, x_test, y_test);
    
    // w baþlangýç deðeri 0.01 olursa
    gradient_descent(learning_rate, x, y, 0.01, x_test, y_test);
    stochastic_gradient_descent(learning_rate, x, y, 0.01, x_test, y_test);
    ADAM(learning_rate, x, y, 0.01, x_test, y_test);
    
    // w baþlangýç deðeri 0.001 olursa
    gradient_descent(learning_rate, x, y, 0.001, x_test, y_test);
    stochastic_gradient_descent(learning_rate, x, y, 0.001, x_test, y_test);
    ADAM(learning_rate, x, y, 0.001, x_test, y_test);
    
    // w baþlangýç deðeri 0.0001 olursa
    gradient_descent(learning_rate, x, y, 0.0001, x_test, y_test);
    stochastic_gradient_descent(learning_rate, x, y, 0.0001, x_test, y_test);
    ADAM(learning_rate, x, y, 0.0001, x_test, y_test);
	
	printf("\nFiles saved successfully.");
	
	// Bellek serbest býrakýlýr
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
