/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkGradientRecursiveGaussianImageFilter.txx,v $
  Language:  C++
  Date:      $Date: 2005/09/28 20:07:51 $
  Version:   $Revision: 1.31 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkGradientRecursiveGaussianImageFilter_txx
#define _itkGradientRecursiveGaussianImageFilter_txx

#include "itkGradientRecursiveGaussianImageFilter.h"
#include "itkImageRegionIteratorWithIndex.h"

namespace itk
{


/**
 * Constructor
 */
template <typename TInputImage, typename TOutputImage >
GradientRecursiveGaussianImageFilter<TInputImage,TOutputImage>
::GradientRecursiveGaussianImageFilter()
{
  m_NormalizeAcrossScale = false;

  for( unsigned int i = 0; i<ImageDimension-1; i++ )
    {
    m_SmoothingFilters[ i ] = GaussianFilterType::New();
    m_SmoothingFilters[ i ]->SetOrder( GaussianFilterType::ZeroOrder );
    m_SmoothingFilters[ i ]->SetNormalizeAcrossScale( m_NormalizeAcrossScale );
    m_SmoothingFilters[ i ]->ReleaseDataFlagOn();
    }

  m_DerivativeFilter = DerivativeFilterType::New();
  m_DerivativeFilter->SetOrder( DerivativeFilterType::FirstOrder );
  m_DerivativeFilter->SetNormalizeAcrossScale( m_NormalizeAcrossScale );
  
  m_DerivativeFilter->SetInput( this->GetInput() );

  m_SmoothingFilters[0]->SetInput( m_DerivativeFilter->GetOutput() );

  for( unsigned int i = 1; i<ImageDimension-1; i++ )
    {
    m_SmoothingFilters[ i ]->SetInput( 
      m_SmoothingFilters[i-1]->GetOutput() );
    }
  
  m_ImageAdaptor = OutputImageAdaptorType::New();

  this->SetSigma( 1.0 );

}


/**
 * Set value of Sigma
 */
template <typename TInputImage, typename TOutputImage>
void 
GradientRecursiveGaussianImageFilter<TInputImage,TOutputImage>
::SetSigma( RealType sigma )
{

  for( unsigned int i = 0; i<ImageDimension-1; i++ )
    {
    m_SmoothingFilters[ i ]->SetSigma( sigma );
    }
  m_DerivativeFilter->SetSigma( sigma );

  this->Modified();

}



/**
 * Set Normalize Across Scale Space
 */
template <typename TInputImage, typename TOutputImage>
void 
GradientRecursiveGaussianImageFilter<TInputImage,TOutputImage>
::SetNormalizeAcrossScale( bool normalize )
{

  m_NormalizeAcrossScale = normalize;

  for( unsigned int i = 0; i<ImageDimension-1; i++ )
    {
    m_SmoothingFilters[ i ]->SetNormalizeAcrossScale( normalize );
    }
  m_DerivativeFilter->SetNormalizeAcrossScale( normalize );

  this->Modified();

}


//
//
//
template <typename TInputImage, typename TOutputImage>
void
GradientRecursiveGaussianImageFilter<TInputImage,TOutputImage>
::GenerateInputRequestedRegion() throw(InvalidRequestedRegionError)
{
  // call the superclass' implementation of this method. this should
  // copy the output requested region to the input requested region
  Superclass::GenerateInputRequestedRegion();

  // This filter needs all of the input
  typename GradientRecursiveGaussianImageFilter<TInputImage,TOutputImage>::InputImagePointer image = const_cast<InputImageType *>( this->GetInput() );
  image->SetRequestedRegion( this->GetInput()->GetLargestPossibleRegion() );
}


//
//
//
template <typename TInputImage, typename TOutputImage>
void
GradientRecursiveGaussianImageFilter<TInputImage,TOutputImage>
::EnlargeOutputRequestedRegion(DataObject *output)
{
  TOutputImage *out = dynamic_cast<TOutputImage*>(output);

  if (out)
    {
    out->SetRequestedRegion( out->GetLargestPossibleRegion() );
    }
}

/**
 * Compute filter for Gaussian kernel
 */
template <typename TInputImage, typename TOutputImage >
void
GradientRecursiveGaussianImageFilter<TInputImage,TOutputImage >
::GenerateData(void)
{
 // Create a process accumulator for tracking the progress of this
  // minipipeline
  ProgressAccumulator::Pointer progress = ProgressAccumulator::New();
  progress->SetMiniPipelineFilter(this);
  
  // Compute the contribution of each filter to the total progress.
  const double weight = 1.0 / ( ImageDimension * ImageDimension );

  for( unsigned int i = 0; i<ImageDimension-1; i++ )
    {
    progress->RegisterInternalFilter( m_SmoothingFilters[i], weight );
    }

  progress->RegisterInternalFilter( m_DerivativeFilter, weight );
  progress->ResetProgress();

  const typename TInputImage::ConstPointer   inputImage( this->GetInput() );

  m_ImageAdaptor->SetImage( this->GetOutput() );

  m_ImageAdaptor->SetLargestPossibleRegion( 
    inputImage->GetLargestPossibleRegion() );

  m_ImageAdaptor->SetBufferedRegion( 
    inputImage->GetBufferedRegion() );

  m_ImageAdaptor->SetRequestedRegion( 
    inputImage->GetRequestedRegion() );

  m_ImageAdaptor->Allocate();

  m_DerivativeFilter->SetInput( inputImage );

  for( unsigned int dim=0; dim < ImageDimension; dim++ )
    {
    unsigned int i=0; 
    unsigned int j=0;
    while(  i < ImageDimension-1 )
      {
      if( i == dim ) 
        {
        j++;
        }
      m_SmoothingFilters[ i ]->SetDirection( j );
      i++;
      j++;
      }
    m_DerivativeFilter->SetDirection( dim );
    
    GaussianFilterPointer lastFilter = m_SmoothingFilters[ImageDimension-2];

    lastFilter->Update();

    progress->ResetFilterProgressAndKeepAccumulatedProgress();

    // Copy the results to the corresponding component
    // on the output image of vectors
    m_ImageAdaptor->SelectNthElement( dim );

    typename RealImageType::Pointer derivativeImage = 
      lastFilter->GetOutput(); 

    ImageRegionIteratorWithIndex< RealImageType > it( 
      derivativeImage, 
      derivativeImage->GetRequestedRegion() );

    ImageRegionIteratorWithIndex< OutputImageAdaptorType > ot( 
      m_ImageAdaptor, 
      m_ImageAdaptor->GetRequestedRegion() );
  
    const RealType spacing = inputImage->GetSpacing()[ dim ];

    it.GoToBegin();
    ot.GoToBegin();
    while( !it.IsAtEnd() )
      {
      ot.Set( it.Get() / spacing );
      ++it;
      ++ot;
      }

    }
  

}


template <typename TInputImage, typename TOutputImage>
void
GradientRecursiveGaussianImageFilter<TInputImage,TOutputImage>
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os,indent);
  os << "NormalizeAcrossScale: " << m_NormalizeAcrossScale << std::endl;
}


} // end namespace itk

#endif
