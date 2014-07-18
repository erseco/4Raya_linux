
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;
#include <string>
using std::string;
#include "stdlib.h"

#include "environment.h"
//#include "random_num_gen.h"
#include"include/GL/glui.h"

Environment::Environment(){
    MAZE_SIZE = 7;
	maze_ = new char*[MAZE_SIZE];
	maze_[0] = new char[MAZE_SIZE*MAZE_SIZE];
	for (int i=1; i<MAZE_SIZE; i++)
	  maze_[i] = &(maze_[i-1][0])+7;

    tope_= new char[MAZE_SIZE];


	for (int col=0; col<MAZE_SIZE; col+=1)
	{
		for (int row=0; row<MAZE_SIZE; row+=1)
		{
		    maze_[row][col]=0;
		}// for - col
		tope_[col]=0;
	}// for - row


    jugador_activo_=1;
    casillas_libres_=49;
    last_action1_=-1;
    last_action2_=-1;
}

// -----------------------------------------------------------
Environment::~Environment(){
    delete [] maze_[0];
    delete [] maze_;

    delete [] tope_;
}
// -----------------------------------------------------------
Environment::Environment(const Environment &env){
    MAZE_SIZE=env.MAZE_SIZE;

	maze_ = new char*[MAZE_SIZE];
	maze_[0] = new char[MAZE_SIZE*MAZE_SIZE];
	for (int i=1; i<MAZE_SIZE; i++)
	  maze_[i] = &(maze_[i-1][0])+7;

    tope_ = new char[MAZE_SIZE];

    for (int i=0; i<MAZE_SIZE; i++)
      for (int j=0; j<MAZE_SIZE; j++)
        maze_[i][j]=env.maze_[i][j];

    for (int i=0; i<MAZE_SIZE; i++)
        tope_[i]=env.tope_[i];

    jugador_activo_=env.jugador_activo_;
    casillas_libres_=env.casillas_libres_;
    last_action1_=env.last_action1_;
    last_action2_=env.last_action2_;

}
// -----------------------------------------------------------
Environment& Environment::operator=(const Environment& env)
{
    if (this == &env) return *this; // handle self assignment

    if (MAZE_SIZE>0){
      delete [] maze_[0];
      delete [] maze_;

      delete [] tope_;
    }

    MAZE_SIZE=env.MAZE_SIZE;

	maze_ = new char*[MAZE_SIZE];
	maze_[0] = new char[MAZE_SIZE*MAZE_SIZE];
	for (int i=1; i<MAZE_SIZE; i++)
	  maze_[i] = &(maze_[i-1][0])+7;

    tope_ = new char[MAZE_SIZE];

    for (int i=0; i<MAZE_SIZE; i++)
      for (int j=0; j<MAZE_SIZE; j++)
        maze_[i][j]=env.maze_[i][j];

    for (int i=0; i<MAZE_SIZE; i++)
        tope_[i]=env.tope_[i];

    jugador_activo_=env.jugador_activo_;
    casillas_libres_=env.casillas_libres_;
    last_action1_=env.last_action1_;
    last_action2_=env.last_action2_;

}
// -----------------------------------------------------------
void Environment::ModificarTablero(const char *origen){
   for (int i=0; i<49; i++)
     maze_[0][i]=origen[i];
}


void Environment::CopiarTablero(char *destino) const{
   for (int i=0; i<49; i++)
     destino[i]=maze_[0][i];
}


// -----------------------------------------------------------
void Environment::Show(int w,int h)
{
    char m[7][7];
    for (int row=0; row<7; row++)
      for (int col=0; col<7; col++)
         m[6-row][col]=maze_[row][col];

    //cout << "Repintando el tablero\n";

	const static float dirty_level=10.0;
	float length=(float)(w>h?h:w)/(float)(MAZE_SIZE+4);
	for (int row=0; row<MAZE_SIZE; row++)
	{
	    //cout << endl;
		for (int col=0; col<MAZE_SIZE; col+=1)
		{
            //cout <<  (char) (maze_[row][col]+'0');
			float x=(col-MAZE_SIZE/2)*length*2+length,y=(MAZE_SIZE/2-row)*length*2-length;
			if (m[row][col] == 1){
				//cout << "XXXXXX";

				glBegin(GL_POLYGON);
					glColor3f(0,1,0);
					glVertex2f(x-(0.9*length),y-(0.9*length));	glVertex2f(x+(0.9*length),y-(0.9*length));
					glVertex2f(x+(0.9*length),y+(0.9*length));	glVertex2f(x-(0.9*length),y+(0.9*length));
				glEnd();
				glBegin(GL_POLYGON);
					glColor3f(1,1,1);
					glVertex2f(x-length,y-length);	glVertex2f(x+length,y-length);
					glVertex2f(x+length,y+length);	glVertex2f(x-length,y+length);
				glEnd();
			}
			else if (m[row][col] == 2){
				//cout << "XXXXXX";

				glBegin(GL_POLYGON);
					glColor3f(0,0,1);
					glVertex2f(x-(0.9*length),y-(0.9*length));	glVertex2f(x+(0.9*length),y-(0.9*length));
					glVertex2f(x+(0.9*length),y+(0.9*length));	glVertex2f(x-(0.9*length),y+(0.9*length));
				glEnd();
				glBegin(GL_POLYGON);
					glColor3f(1,1,1);
					//glColor3f(((float)(dirty_level-maze_[row][col]))/dirty_level,((float)(dirty_level-maze_[row][col]))/dirty_level,((float)(dirty_level-maze_[row][col]))/dirty_level);
					glVertex2f(x-length,y-length);	glVertex2f(x+length,y-length);
					glVertex2f(x+length,y+length);	glVertex2f(x-length,y+length);
				glEnd();
			}
			else if (m[row][col] == 3){
				//cout << "XXXXXX";

				glBegin(GL_POLYGON);
					glColor3f(0,0,0);
					glVertex2f(x-(0.3*length),y-(0.3*length));	glVertex2f(x+(0.3*length),y-(0.3*length));
					glVertex2f(x+(0.3*length),y+(0.3*length));	glVertex2f(x-(0.3*length),y+(0.3*length));
				glEnd();
				glBegin(GL_POLYGON);
					glColor3f(0,1,0);
					glVertex2f(x-(0.9*length),y-(0.9*length));	glVertex2f(x+(0.9*length),y-(0.9*length));
					glVertex2f(x+(0.9*length),y+(0.9*length));	glVertex2f(x-(0.9*length),y+(0.9*length));
				glEnd();
				glBegin(GL_POLYGON);
					glColor3f(1,1,1);
					glVertex2f(x-length,y-length);	glVertex2f(x+length,y-length);
					glVertex2f(x+length,y+length);	glVertex2f(x-length,y+length);
				glEnd();
			}
			else if (m[row][col] == 4){
				//cout << "XXXXXX";

				glBegin(GL_POLYGON);
					glColor3f(0,0,0);
					glVertex2f(x-(0.3*length),y-(0.3*length));	glVertex2f(x+(0.3*length),y-(0.3*length));
					glVertex2f(x+(0.3*length),y+(0.3*length));	glVertex2f(x-(0.3*length),y+(0.3*length));
				glEnd();
				glBegin(GL_POLYGON);
					glColor3f(0,0,1);
					glVertex2f(x-(0.9*length),y-(0.9*length));	glVertex2f(x+(0.9*length),y-(0.9*length));
					glVertex2f(x+(0.9*length),y+(0.9*length));	glVertex2f(x-(0.9*length),y+(0.9*length));
				glEnd();
				glBegin(GL_POLYGON);
					glColor3f(1,1,1);
					//glColor3f(((float)(dirty_level-maze_[row][col]))/dirty_level,((float)(dirty_level-maze_[row][col]))/dirty_level,((float)(dirty_level-maze_[row][col]))/dirty_level);
					glVertex2f(x-length,y-length);	glVertex2f(x+length,y-length);
					glVertex2f(x+length,y+length);	glVertex2f(x-length,y+length);
				glEnd();
			}
			else
			{
				glBegin(GL_POLYGON);
					glColor3f(0.9,0.9,0.9);
					glVertex2f(x-(0.9*length),y-(0.9*length));	glVertex2f(x+(0.9*length),y-(0.9*length));
					glVertex2f(x+(0.9*length),y+(0.9*length));	glVertex2f(x-(0.9*length),y+(0.9*length));
				glEnd();
				glBegin(GL_POLYGON);
					glColor3f(1,1,1);
					//glColor3f(((float)(dirty_level-maze_[row][col]))/dirty_level,((float)(dirty_level-maze_[row][col]))/dirty_level,((float)(dirty_level-maze_[row][col]))/dirty_level);
					glVertex2f(x-length,y-length);	glVertex2f(x+length,y-length);
					glVertex2f(x+length,y+length);	glVertex2f(x-length,y+length);
				glEnd();
				//cout << symbol;
				//cout << setw(4) << maze_[row][col];
				//cout << symbol;


			}
		}// for - col
		//cout << endl;
	}// for - row
    for (int row=0; row<7; row++)
      for (int col=0; col<7; col++)
          if (maze_[row][col]>2)
             maze_[row][col]-=2;


}
// -----------------------------------------------------------
void Environment::Change()
{
}
// -----------------------------------------------------------
void Environment::AcceptAction(Environment::ActionType action)
{
    //cout << "AcceptAction: " << ActionStr(action) << endl;
    int i;
    switch (action){
		case Environment::PUT1:
                                maze_[tope_[0]][0]=jugador_activo_;
                                casillas_libres_--;
                                tope_[0]++;
                                break;
		case Environment::PUT2:
                                maze_[tope_[1]][1]=jugador_activo_;
                                casillas_libres_--;
                                tope_[1]++;
                                break;
		case Environment::PUT3:
                                maze_[tope_[2]][2]=jugador_activo_;
                                casillas_libres_--;
                                tope_[2]++;
                                break;
		case Environment::PUT4:
                                maze_[tope_[3]][3]=jugador_activo_;
                                casillas_libres_--;
                                tope_[3]++;
                                break;
		case Environment::PUT5:
                                maze_[tope_[4]][4]=jugador_activo_;
                                casillas_libres_--;
                                tope_[4]++;
                                break;
		case Environment::PUT6:
                                maze_[tope_[5]][5]=jugador_activo_;
                                casillas_libres_--;
                                tope_[5]++;
                                break;
		case Environment::PUT7:
                                maze_[tope_[6]][6]=jugador_activo_;
                                casillas_libres_--;
                                tope_[6]++;
                                break;
    }

    if (jugador_activo_==1)
        last_action1_ = (int) (action);
    else
        last_action2_ = (int) (action);


}
// -----------------------------------------------------------
int Environment::possible_actions(bool *act) const{

   for (int i=0; i<7; i++)
     if (tope_[i]<7)
        act[i]=true;
     else
        act[i]=false;


    int n_act=0;
    for (int i=0; i<7; i++)
      if (act[i])
        n_act++;

    return n_act;
}

//------------------------------------------------------------------------

int Environment::GenerateAllMoves(Environment *V) const{
  bool act[7];
  int n_act=0;
  possible_actions(act);
  for (int i=0; i<7; i++){
    if (act[i]){
       V[n_act] = *this;
       V[n_act].AcceptAction(static_cast<ActionType> (i));
       V[n_act].ChangePlayer();
       n_act++;
    }
  }
  return n_act;
}

Environment Environment::GenerateNextMove(int &act) const{
    bool posibles[7];
    possible_actions(posibles);
    act++;
    while (act<7 and !posibles[act])
      act++;
    if (act>6){
        return *this;
    }
    else{
        Environment nuevo = *this;
        nuevo.AcceptAction(static_cast<ActionType> (act));
        nuevo.ChangePlayer();
        return nuevo;
    }
}

// -----------------------------------------------------------
int Environment::Last_Action(int jug) const{
    if (jug==1)
      return last_action1_;
    else
      return last_action2_;
}
// -----------------------------------------------------------
bool Environment::EnLinea(int fila, int columna, int &ganador) const{
    ganador=0;
    //En la misma Fila
    if (columna<4){
      if (maze_[fila][columna]   == maze_[fila][columna+1] and
          maze_[fila][columna+1] == maze_[fila][columna+2] and
          maze_[fila][columna+2] == maze_[fila][columna+3]){
          //cout << "En la misma fila\n";
          ganador=maze_[fila][columna];
          return true;
      }
    }
    //En la misma columna
    if (fila<4){
      if (maze_[fila][columna]   == maze_[fila+1][columna] and
          maze_[fila+1][columna] == maze_[fila+2][columna] and
          maze_[fila+2][columna] == maze_[fila+3][columna]){
          //cout << "En la misma columna\n";

          ganador=maze_[fila][columna];
          return true;
      }
    }
    //En la diagonal hacia arriba
    if (fila<4 and columna<4){
      if (maze_[fila][columna]   == maze_[fila+1][columna+1] and
          maze_[fila+1][columna+1] == maze_[fila+2][columna+2] and
          maze_[fila+2][columna+2] == maze_[fila+3][columna+3]){
          //cout << "En la diagonal principal\n";

          ganador=maze_[fila][columna];
          return true;
      }
    }

    //En la diagonal hacia abajo
    if (fila>2 and columna<4){
      if (maze_[fila][columna]   == maze_[fila-1][columna+1] and
          maze_[fila-1][columna+1] == maze_[fila-2][columna+2] and
          maze_[fila-2][columna+2] == maze_[fila-3][columna+3]){
          //cout << "En la diagonal secundaria\n";

          ganador=maze_[fila][columna];
          return true;
      }
    }

    return false;

}


// -----------------------------------------------------------
bool Environment::EnLinea2(int fila, int columna, int &ganador) const{
    ganador=0;
    //En la misma Fila
    if (columna<4){
      if (maze_[fila][columna]   == maze_[fila][columna+1] and
          maze_[fila][columna+1] == maze_[fila][columna+2] and
          maze_[fila][columna+2] == maze_[fila][columna+3]){
          //cout << "En la misma fila\n";
          ganador=maze_[fila][columna];
          maze_[fila][columna]=ganador+2;
          maze_[fila][columna+1]=ganador+2;
          maze_[fila][columna+2]=ganador+2;
          maze_[fila][columna+3]=ganador+2;
          return true;
      }
    }
    //En la misma columna
    if (fila<4){
      if (maze_[fila][columna]   == maze_[fila+1][columna] and
          maze_[fila+1][columna] == maze_[fila+2][columna] and
          maze_[fila+2][columna] == maze_[fila+3][columna]){
          //cout << "En la misma columna\n";

          ganador=maze_[fila][columna];
          maze_[fila][columna]=ganador+2;
          maze_[fila+1][columna]=ganador+2;
          maze_[fila+2][columna]=ganador+2;
          maze_[fila+3][columna]=ganador+2;
          return true;
      }
    }
    //En la diagonal hacia arriba
    if (fila<4 and columna<4){
      if (maze_[fila][columna]   == maze_[fila+1][columna+1] and
          maze_[fila+1][columna+1] == maze_[fila+2][columna+2] and
          maze_[fila+2][columna+2] == maze_[fila+3][columna+3]){
          //cout << "En la diagonal principal\n";

          ganador=maze_[fila][columna];
          maze_[fila][columna]=ganador+2;
          maze_[fila+1][columna+1]=ganador+2;
          maze_[fila+2][columna+2]=ganador+2;
          maze_[fila+3][columna+3]=ganador+2;
          return true;
      }
    }

    //En la diagonal hacia abajo
    if (fila>2 and columna<4){
      if (maze_[fila][columna]   == maze_[fila-1][columna+1] and
          maze_[fila-1][columna+1] == maze_[fila-2][columna+2] and
          maze_[fila-2][columna+2] == maze_[fila-3][columna+3]){
          //cout << "En la diagonal secundaria\n";

          ganador=maze_[fila][columna];
          maze_[fila][columna]=ganador+2;
          maze_[fila-1][columna+1]=ganador+2;
          maze_[fila-2][columna+2]=ganador+2;
          maze_[fila-3][columna+3]=ganador+2;
          return true;
      }
    }

    return false;

}


// -----------------------------------------------------------
bool Environment::JuegoTerminado() const{
    if (casillas_libres_==0){
      //cout << "Juego Terminado\n";
      return true;
    }

    bool cuatro_en_raya=false;
    int ganador;

    for (int i=0; !cuatro_en_raya and i<7; i++)
      for (int j=0; !cuatro_en_raya and j<7; j++){
          if (maze_[i][j]!=0)
            cuatro_en_raya=EnLinea(i,j,ganador);
      }

    /*if (cuatro_en_raya)
            cout << "Juego Terminado\n";*/

    return cuatro_en_raya;
}

// -----------------------------------------------------------
int Environment::RevisarTablero() const{
    bool cuatro_en_raya=false;
    int ganador;

    for (int i=0; !cuatro_en_raya and i<7; i++)
      for (int j=0; !cuatro_en_raya and j<7; j++){
          if (maze_[i][j]!=0)
            cuatro_en_raya=EnLinea(i,j,ganador);
      }

    if (cuatro_en_raya)
       return ganador;
    else
       return 0;
}


// -----------------------------------------------------------
int Environment::RevisarTablero2() const{
    bool cuatro_en_raya=false;
    int ganador;

    for (int i=0; !cuatro_en_raya and i<7; i++)
      for (int j=0; !cuatro_en_raya and j<7; j++){
          if (maze_[i][j]!=0)
            cuatro_en_raya=EnLinea2(i,j,ganador);
      }

    if (cuatro_en_raya)
       return ganador;
    else
       return 0;
}

// -----------------------------------------------------------
bool Environment::operator==(const Environment & env) const{
    bool iguales=true;
    for (int i=0; i<MAZE_SIZE and iguales; i++)
      for (int j=0; j<MAZE_SIZE and iguales; j++)
        if (maze_[i][j]!=env.maze_[i][j])
          iguales=false;
    return iguales;
}



void Environment::PintaTablero()const{
  for (int row=6; row>=0; row--){
     for (int col=0; col<7; col++){
        cout << (char) (maze_[row][col]+48);
     }
    cout << endl;
  }
}


string Environment::ActionStr(ActionType action)
{
	switch (action)
	{
	case Environment::PUT1: return "PUT 1";
	case Environment::PUT2: return "PUT 2";
	case Environment::PUT3: return "PUT 3";
	case Environment::PUT4: return "PUT 4";
	case Environment::PUT5: return "PUT 5";
	case Environment::PUT6: return "PUT 6";
	case Environment::PUT7: return "PUT 7";
	default: return "???";
	}
}

