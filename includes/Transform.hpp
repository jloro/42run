#ifndef TRANSFORM_HPP
# define TRANSFORM_HPP

# include <glm.hpp>
# include <iostream>
# include <memory>

struct Transform
{
    public :
/*  constructors / destructors    */
    Transform(void);
    Transform(const Transform &src);
    Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, std::shared_ptr<Transform> parent = nullptr);
    Transform(glm::vec3 pos, glm::vec3 scale, std::shared_ptr<Transform> parent = nullptr);
    Transform(glm::vec3 pos, std::shared_ptr<Transform> parent = nullptr);
    virtual ~Transform(void);
/*  public variables    */
    glm::vec3	position;
    glm::vec3	rotation;
    glm::vec3	scale;
    std::shared_ptr<Transform> parent;
/*  public functions    */
    std::string const toString(void) const;
    Transform &		operator=(const Transform & rhs);
    private:
        void    _Initialize(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, std::shared_ptr<Transform> parent = nullptr);
};
#endif

std::ostream &	operator<< (std::ostream & o, const Transform & rhs);