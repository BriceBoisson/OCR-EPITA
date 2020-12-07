# include <gtk/gtk.h>
# include <stdio.h>
# include <stdlib.h>
# include <err.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

GtkWidget *window;
GtkWidget *wimage;
GtkWidget *image;
GtkWidget *textBox;
GtkWidget *final;
GtkWidget *ninety;
GtkWidget *segm;
GtkWidget *grays;
GtkWidget *contra;
GtkWidget *biner;
GtkWidget *play;
SDL_Surface *surf;

int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO);
  GtkBuilder *builder;
  gtk_init(&argc, &argv);
  builder = gtk_builder_new();
  gtk_builder_add_from_file (builder, "main.glade", NULL);
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  gtk_builder_connect_signals(builder, NULL);
  final = GTK_WIDGET(gtk_builder_get_object(builder, "final"));
  textBox = GTK_WIDGET(gtk_builder_get_object(builder, "textBox"));
  ninety = GTK_WIDGET(gtk_builder_get_object(builder, "ninety"));
  segm = GTK_WIDGET(gtk_builder_get_object(builder, "segmentation"));
  grays = GTK_WIDGET(gtk_builder_get_object(builder, "grayscale"));
  contra  = GTK_WIDGET(gtk_builder_get_object(builder, "contrastes"));
  biner = GTK_WIDGET(gtk_builder_get_object(builder, "binarisation"));
  play = GTK_WIDGET(gtk_builder_get_object(builder, "lanceTout"));
  g_object_unref(builder);
  gtk_widget_show(window);
  gtk_main();
  return 0;
}

SDL_Surface* load_image(char *path)
{
  SDL_Surface *img;
  img = IMG_Load(path);
  if (!img)
    errx(3, "Can't load %s: %s", path, IMG_GetError());
  return img;
}


void choose_image(char *file)
{
  gtk_widget_set_sensitive(ninety, TRUE); 
  gtk_widget_set_sensitive(segm, TRUE);
  gtk_widget_set_sensitive(play, TRUE);
  gtk_widget_set_sensitive(grays, TRUE);
  gtk_widget_set_sensitive(contra, TRUE);
  gtk_widget_set_sensitive(biner, TRUE);
  surf = load_image(file);
  SDL_SaveBMP(surf, "images/temp.bmp"); // L'image ou tu dois appliquer les fonctions est save dans images/temp.bmp
  SDL_FreeSurface(surf);
}

void file_selected(GtkWidget *filechooserbutton)
{
  char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooserbutton));
  printf("%s\n", filename);
  choose_image(filename);
}

void play_button()
{
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textBox));
  GtkTextIter iter;
  gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
  char *result = malloc(sizeof(char) * 100000);


  //fait toutes les étapes sur la variable 'result' qui doit etre le texte renvoyé par le reseau de neurones


  gtk_text_buffer_insert(buffer, &iter, result, -1);
  gtk_widget_show(final);
  gtk_widget_hide(window);
}



// Pour les fonctions, l'image à modifier est sauvegardée dans le fichier images/temp.bmp

void plus_ninety()
{
  //rotation + 90 degré
}

void gray()
{
  //grayscale
}

void bine()
{
  //binarisation
}

void seg()
{
  //segmentation
}

void cont()
{
  //constrastes
}

void on_quit_clicked()
{ 
  gtk_main_quit();
}
