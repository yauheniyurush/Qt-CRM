
#ifndef BUTTONSDLG_H
#define BUTTONSDLG_H
#include "QFrame.h"

#include <string>

namespace CRM {


/**
  * class ButtonsDlg
  * 
  */

class ButtonsDlg : public QFrame
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  ButtonsDlg ();

  /**
   * Empty Destructor
   */
  virtual ~ButtonsDlg ();

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
   ButtonsDlg (QWidget* parent)
  {
  }


  /**
   * @param
   */
  void error_message (const QString& )
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
   */
  void accepted ()
  {
  }


  /**
   */
  void rejected ()
  {
  }

private:

  // Static Private attributes
  //  

  // Private attributes
  //  

  Ui::ButtonsFrame ui;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of ui
   * @param new_var the new value of ui
   */
  void setUi (Ui::ButtonsFrame new_var)   {
      ui = new_var;
  }

  /**
   * Get the value of ui
   * @return the value of ui
   */
  Ui::ButtonsFrame getUi ()   {
    return ui;
  }
private:


  void initAttributes () ;

};
} // end of package namespace

#endif // BUTTONSDLG_H
