#ifndef __Exception_H_
#define __Exception_H_

class Exception : public std::exception {
public:
    Exception(const int code, const std::string &text) : std::exception(),
                                                       _errorText(text),
                                                       _code(code) {

    }

    /**
    * Destructor.
    */
    virtual ~Exception() throw() {
    }

    /**
    * Returns the error text.
    */
    std::string error() const {
        return (_errorText);
    }

    /**
    * Returns the error id.
    */
    const int code() const {
        return _code;
    }

private:

    /**
    * The text of the exception message.
    */
    std::string _errorText;
    /**
    * The argument related to this exception.
    */
    const int _code;

};


#endif //__Exception_H_
