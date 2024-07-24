// ErrorDomain include guard following SWS_CORE_90001]
#ifndef ARA_CORE_ERROR_DOMAIN_H_
#define ARA_CORE_ERROR_DOMAIN_H_

    // forward decleratio  of ErrorCode as a stub to be able to build the type
    class ErrorCode;
    namespace ara
    {
        namespace core
        {
            // Encapsulation of an error domain.
            // An error domain is the controlling entity for ErrorCode’s error code values, and defines the
            // mapping of such error code values to textual representations.
            // This class is a literal type, and subclasses are strongly advised to be literal types as well.
            class ErrorDomain
            {   
                public:
                    // Alias type for a unique ErrorDomain identifier type
                    // using IdType = std::unit64_t;
                    using IdType = double;
                    // Alias type for a domain-specific error code value
                    //using CodeType = std::unit32_t;
                    using CodeType = unsigned int;
                    // Alias type for vendor-specific supplementary data 
                    //using SupportDataType = <implmentation-defined>;

                    // Copy construction shall be disabled
                    ErrorDomain( const ErrorDomain & ) =delete;
                    // Move construction shall be disabled.
                    ErrorDomain( ErrorDomain && ) =delete;
                    // Copy assignment shall be disabled
                    ErrorDomain& operator= (const ErrorDomain &) =delete;
                    // Move assignment shall be disabled.
                    ErrorDomain& operator= (ErrorDomain &&) =delete;
                    // Compare for equality with another ErrorDomain instance.
                    // Two ErrorDomain instances compare equal when their identifiers (returned by Id()) are equal
                    constexpr bool operator== (const ErrorDomain &other) const noexcept
                    {
                        return this->Id() == other.Id();
                    }
                    // Compare for non-equality with another ErrorDomain instance
                    constexpr bool operator!= (const ErrorDomain &other) const noexcept
                    {
                        return this->Id()!= other.Id();
                    }
                    // Return the unique domain identifier.
                    constexpr IdType Id () const noexcept
                    {
                        return id;
                    }
                    // Return the name of this error domain.
                    // The returned pointer remains owned by class ErrorDomain and shall not be freed by clients.
                    virtual const char* Name () const noexcept =0;
                    // Return a textual representation of the given error code.
                    // It is a Violation if the errorCode did not originate from this error domain, and thus be subject to
                    // SWS_CORE_00003.
                    // The returned pointer remains owned by the ErrorDomain subclass and shall not be freed by
                    // clients.
                    virtual const char* Message (CodeType errorCode) const noexcept =0;
                    // Throw the given error as exception.
                    // This function will determine the appropriate exception type for the given ErrorCode and throw it.
                    // The thrown exception will contain the given ErrorCode.
                    virtual void ThrowAsException (const ErrorCode &errorCode) const noexcept(false) =0;

                protected:
                    // Construct a new instance with the given identifier.
                    // Identifiers are expected to be system-wide unique
                    explicit constexpr ErrorDomain (IdType id) noexcept
                    :id(id)
                    {
                        ;
                    }
                    // Destructor.
                    // This dtor is non-virtual (and trivial) so that this class can be a literal type. While this class has
                    // virtual functions, no polymorphic destruction is needed
                    ~ErrorDomain() =default;

                private:
                    IdType id;
            };
        }
    }

#endif
