/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and COPYING.LESSER.
 *
 * Copyright:     (c) 1997-2012 Lawrence Livermore National Security, LLC
 * Description:   SparseDataFactory
 *
 ************************************************************************/

#ifndef included_pdat_SparseDataFactory
#define included_pdat_SparseDataFactory

#include "SAMRAI/SAMRAI_config.h"

/*
 ************************************************************************
 *  THIS CLASS WILL BE UNDEFINED IF THE LIBRARY IS BUILT WITHOUT BOOST
 ************************************************************************
 */
#ifdef HAVE_BOOST_HEADERS

#include "SAMRAI/hier/Box.h"
#include "SAMRAI/hier/IntVector.h"
#include "SAMRAI/hier/Patch.h"
#include "SAMRAI/hier/PatchData.h"
#include "SAMRAI/hier/PatchDataFactory.h"

#include "boost/shared_ptr.hpp"

namespace SAMRAI {
namespace pdat {

/*!
 * @brief Factory class used to allocate new instances of SparseData objects.
 *
 * @see pdat::SparseData
 * @see pdat::SparseDataVariable
 * @see hier::PatchDataFactory
 */
template<typename BOX_GEOMETRY>
class SparseDataFactory:public hier::PatchDataFactory
{
public:
   /*!
    * @brief Default constructor for SparseDataFactory class.
    *
    * The ghost cell width argument gives the default width for all
    * sparse data objects created with this factory.
    *
    * @param [in] ghosts The default ghost width
    * @param [in] numDblAttributes The number of double (value) attributes
    * @param [in] numIntAttributes The number of integer (value) attributes
    */
   SparseDataFactory(
      const hier::IntVector& ghosts,
      const std::vector<std::string>& dbl_attributes,
      const std::vector<std::string>& int_attributes);

   /*!
    * @brief Default destructor
    */
   ~SparseDataFactory<BOX_GEOMETRY>();

   /*!
    * @brief Clone a patch data factory
    *
    * @return a cloned factory with the same properties which can
    * then be changed without modifying the original.
    * @param [in] ghosts
    */
   boost::shared_ptr<hier::PatchDataFactory>
   cloneFactory(
      const hier::IntVector& ghosts);

   /*!
    * @brief Allocate a conrete sparse data object.
    *
    * The default informaiton about the object (e.g., ghost cell width)
    * is provided by the factory.
    *
    * @param [in] patch
    */
   boost::shared_ptr<hier::PatchData>
   allocate(
      const hier::Patch& patch) const;

   /*!
    * @brief Allocate the box geomtry object associated with the patch data.
    *
    * This information will be used in the computation of intersections
    * and data dependencies between objects.
    *
    * @param [in] box
    */
   boost::shared_ptr<hier::BoxGeometry>
   getBoxGeometry(
      const hier::Box& box) const;

   /*!
    * @brief Calculate the amount of memory needed to store the sparse data
    * object.
    *
    * The calculation includes object data, and does not include dynamically
    * allocated data.
    */
   size_t
   getSizeOfMemory(
      const hier::Box& box) const;

   /*!
    * @brief Returns true
    *
    * Sparse data quantities will always be treated as though fine values
    * represent tehm on coarse-fine interfaces.
    *
    * @see SparseDataVariable
    */
   bool
   fineBoundaryRepresentsVariable() const {
      return true;
   }

   /*!
    * @brief Returns false.
    *
    * Sparse data space matches the cell-centered index space for AMR patches,
    * hence sparse data does not live on patch borders.
    */
   bool
   dataLivesOnPatchBorder() const {
      return false;
   }

   /*!
    * @brief Returns true if it is valid to copy this SparseDataFactory.
    *
    * If the destination PatchDataFactory is of the same type and dimension,
    * a valid copy can be made.
    */
   bool
   validCopyTo(
      const boost::shared_ptr<PatchDataFactory>& dst_pdf) const;

private:
   /*
    * Copy constructor and assignment operator are made private to
    * ensure the compiler does not create a default implementation.
    */
   SparseDataFactory(
      const SparseDataFactory<BOX_GEOMETRY>& rhs);

   SparseDataFactory<BOX_GEOMETRY>&
   operator = (
      const SparseDataFactory<BOX_GEOMETRY>& rhs);

   std::vector<std::string> d_dbl_attributes;
   std::vector<std::string> d_int_attributes;
};

} // end namespace pdat
} // end namespace SAMRAI

#include "SAMRAI/pdat/SparseDataFactory.C"

#endif
#endif
