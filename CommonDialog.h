
#ifndef COMMONDIALOG_H
#define COMMONDIALOG_H
#include "QDialog.h"

#include <string>

namespace CRM {


/**
  * class CommonDialog
  * 
  */

class CommonDialog : public QDialog
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  CommonDialog ();

  /**
   * Empty Destructor
   */
  virtual ~CommonDialog ();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * @param  parent
   */
   CommonDialog (QWidget* parent)
  {
  }

protected:

  // Static Protected attributes
  //  

  // Protected attributes
  //  

public:


  // Protected attribute accessor methods
  //  

protected:

public:


  // Protected attribute accessor methods
  //  

protected:



  /**
   * @param  central
   */
  void setCentralFrame (QFrame* central)
  {
  }


  /**
   * @param  pOK
   */
  void check_data (bool* pOK)
  {
  }


  /**
   */
  void save ()
  {
  }

private:

  // Static Private attributes
  //  

  // Private attributes
  //  

  ButtonsDlg* pButtons;
  QFrame* pFrame;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of pButtons
   * @param new_var the new value of pButtons
   */
  void setPButtons (ButtonsDlg* new_var)   {
      pButtons = new_var;
  }

  /**
   * Get the value of pButtons
   * @return the value of pButtons
   */
  ButtonsDlg* getPButtons ()   {
    return pButtons;
  }

  /**
   * Set the value of pFrame
   * @param new_var the new value of pFrame
   */
  void setPFrame (QFrame* new_var)   {
      pFrame = new_var;
  }

  /**
   * Get the value of pFrame
   * @return the value of pFrame
   */
  QFrame* getPFrame ()   {
    return pFrame;
  }
private:



  /**
   */
  void accept_pressed ()
  {
  }

  void initAttributes () ;

};
} // end of package namespace

#endif // COMMONDIALOG_H
