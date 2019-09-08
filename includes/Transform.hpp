#ifndef TRANSFORM_HPP
# define TRANSFORM_HPP

# include <glm.hpp>
# include <iostream>

struct Transform
{
    public :
/*  constructors / destructors    */
    Transform(void);
    Transform(const Transform &src);
    Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
    Transform(glm::vec3 pos, glm::vec3 scale);
    Transform(glm::vec3 pos);
    virtual ~Transform(void);
/*  public variables    */
    glm::vec3	position;
    glm::vec3	rotation;
    glm::vec3	scale;
/*  public functions    */
    std::string const toString(void) const;
    Transform &		operator=(const Transform & rhs);
    private:
        void    _Initialize(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
};
#endif

std::ostream &	operator<< (std::ostream & o, const Transform & rhs);