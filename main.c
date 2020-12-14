# include <gtk/gtk.h>
# include <stdio.h>
# include <stdlib.h>
# include <err.h>
# include <SDL2/SDL.h>
#include "all.h"


GtkWidget *window;
GtkWidget *wimage;
GtkWidget *image;
GtkWidget *textBox;
GtkWidget *final;
GtkWidget *ninety;
GtkWidget *oneeighty;
GtkWidget *segm;
GtkWidget *grays;
GtkWidget *contra;
GtkWidget *biner;
GtkWidget *play;
GtkWidget *noise;
GtkWidget *rotation;
GtkWidget *nette;
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
  oneeighty = GTK_WIDGET(gtk_builder_get_object(builder, "oneeighty"));
  segm = GTK_WIDGET(gtk_builder_get_object(builder, "segmentation"));
  grays = GTK_WIDGET(gtk_builder_get_object(builder, "grayscale"));
  contra  = GTK_WIDGET(gtk_builder_get_object(builder, "contrastes"));
  biner = GTK_WIDGET(gtk_builder_get_object(builder, "binarisation"));
  play = GTK_WIDGET(gtk_builder_get_object(builder, "lanceTout"));
  noise = GTK_WIDGET(gtk_builder_get_object(builder, "noise"));
  rotation = GTK_WIDGET(gtk_builder_get_object(builder, "rotation"));
  nette = GTK_WIDGET(gtk_builder_get_object(builder, "nettete"));
  g_object_unref(builder);
  gtk_widget_show(window);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_main();

  return 0;
}

SDL_Surface* load_image(char *path)
{
  SDL_Surface *img;
  img = SDL_LoadBMP(path);
  if (!img)
    errx(3, "Can't load %s: %s", path, SDL_GetError());
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
  gtk_widget_set_sensitive(noise, TRUE);
  gtk_widget_set_sensitive(rotation, TRUE);
  gtk_widget_set_sensitive(oneeighty, TRUE);
  gtk_widget_set_sensitive(nette, TRUE);
  surf = load_image(file);
  SDL_SaveBMP(surf, "images/temp.bmp");
  SDL_FreeSurface(surf);
}

void file_selected(GtkWidget *filechooserbutton)
{
  char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooserbutton));
  printf("%s\n", filename);
  choose_image(filename);
}


// Il faut juste que tu mettes tes fonctions à la place des commentaires. Si jamais tu as pas certaines fonctions
// par exemple pour recup le resultat du reseau de neurones dis le moi et je les demanderai à Axelle ou Brice.


// Pour les fonctions, l'image à modifier est sauvegardée dans le fichier images/temp.bmp


void play_button()
{
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textBox));
  GtkTextIter iter;
  gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
  char *result = calloc(sizeof(char), 10000);


  // result sera le texte final
  // traitement de l'image (dans le fichier images/temp.bmp)
  // segmentation de l'image
  // envoi au reseau de neurones
  // stockage du resultat du reseau de neurones dans la variable result
  SDL_Surface * loadedImage = SDL_LoadBMP("images/temp.bmp");
  binerize(loadedImage);
  Neural_Network network = Initialisation();
  Load_Network(&network, "try2.txt");
  __extractpar(loadedImage,&network,result);
  printf("%s",result);
  Free_Network(&network);
  SDL_FreeSurface(loadedImage);
  gtk_text_buffer_insert(buffer, &iter, result, -1);
  free(result);
  gtk_widget_show(final);
  gtk_widget_hide(window);
}

void nettete()
{
  SDL_Surface * loadedImage = SDL_LoadBMP("images/temp.bmp");
  SDL_Window* window = display_img(loadedImage);
  wait_for_keypressed();
  SDL_DestroyWindow(window);
  loadedImage = Convolute(loadedImage,SharpenMatrix);
  window = display_img(loadedImage);
  SDL_SaveBMP(loadedImage,"images/temp.bmp");
  wait_for_keypressed();
  SDL_DestroyWindow(window);
  SDL_FreeSurface(loadedImage); 
}

void plus_oneeighty()
{
  SDL_Surface * loadedImage = SDL_LoadBMP("images/temp.bmp");
  SDL_Window* window = display_img(loadedImage);
  wait_for_keypressed();
  SDL_DestroyWindow(window);
  loadedImage = rotate(180,loadedImage);
  window = display_img(loadedImage);         
 display_img(loadedImage);
 SDL_SaveBMP(loadedImage,"images/temp.bmp");
 wait_for_keypressed();
 SDL_DestroyWindow(window);
 SDL_FreeSurface(loadedImage); 
}

void plus_ninety()
{
  SDL_Surface * loadedImage = SDL_LoadBMP("images/temp.bmp");
  SDL_Window* window = display_img(loadedImage);
  wait_for_keypressed();
  SDL_DestroyWindow(window);
  grayscale(loadedImage);         
  binerize(loadedImage); 
  loadedImage = rotate(90,loadedImage);           
  window = display_img(loadedImage);
  SDL_SaveBMP(loadedImage,"images/temp.bmp");
  wait_for_keypressed();
  SDL_DestroyWindow(window);
  SDL_FreeSurface(loadedImage);   
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

}

void cont()
{
  SDL_Surface * loadedImage = SDL_LoadBMP("images/temp.bmp");
  SDL_Window* window = display_img(loadedImage);
  wait_for_keypressed();
  SDL_DestroyWindow(window);
  ConstrastRenforcement(loadedImage,100);
  window = display_img(loadedImage);
  wait_for_keypressed();
   SDL_DestroyWindow(window);
  SDL_FreeSurface(loadedImage);  
}

void rot()
{
  SDL_Surface * loadedImage = SDL_LoadBMP("images/temp.bmp");
  SDL_Window* window = display_img(loadedImage);
  wait_for_keypressed();
  SDL_DestroyWindow(window);
  grayscale(loadedImage);         
  binerize(loadedImage);    
  double teta = houghtrasformy(loadedImage);

  if (teta > 90)
  {
    teta+=90;
  }
  else
  {
    teta-=90;
  }
  loadedImage = rotate(teta,loadedImage);           
  window = display_img(loadedImage);
  SDL_SaveBMP(loadedImage,"images/temp.bmp");
  wait_for_keypressed();
  SDL_DestroyWindow(window);
  SDL_FreeSurface(loadedImage);        
}

void noise_reduction()
{
  SDL_Surface * loadedImage = SDL_LoadBMP("images/temp.bmp");
  SDL_Window* window = display_img(loadedImage);
  wait_for_keypressed();
  SDL_DestroyWindow(window);
  noiseReduction(loadedImage);
  window = display_img(loadedImage);  
  wait_for_keypressed();
  SDL_DestroyWindow(window);
}

void on_quit_clicked()
{ 
  gtk_main_quit();
}
