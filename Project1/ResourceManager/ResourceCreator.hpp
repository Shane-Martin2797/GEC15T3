////////////////////////////////////////////////////////////
//
// The MIT License (MIT)
//
// Copyright (c) 2014 stevehalliwell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
////////////////////////////////////////////////////////////

#ifndef RESOURCE_CREATOR_HPP
#define RESOURCE_CREATOR_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "BaseResource.hpp"
//#include <ResourceManager/BaseResource.hpp>
#include <memory>

namespace rm 
{
////////////////////////////////////////////////////////////
/// \brief ResourceCreatorInterface and 
///     ResourceCreatorImplementation are helper classes 
///     that allow the ResourceFactory to create
///     specific resources without static type information
////////////////////////////////////////////////////////////

class ResourceCreatorInterface 
{
public:
    virtual std::shared_ptr<BaseResource> create() = 0;
};


template<class T>
class ResourceCreatorImplementation : public ResourceCreatorInterface
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Creates a new resource of type T
    ///
    /// \returns A downcasted pointer to a new resource T
    ////////////////////////////////////////////////////////////
    std::shared_ptr<BaseResource> create() override;
};

//#include <ResourceManager/ResourceCreator.inl>
#include "ResourceCreator.inl"
}

#endif //RESOURCE_ALLOCATOR_HPP
