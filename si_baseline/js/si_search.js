(function ($) {
  if (!Drupal.siSearch) {
    Drupal.siSearch = {};
  }
  var hasRun = false;

  Drupal.siSearch.splitList = function (list, num_cols, listItem) {
    //listItem = 'li',
    listClass = 'sub-list';
    list.each(function () {
      var items_per_col = new Array(),
        items = $(this).find(listItem),
        min_items_per_col = Math.floor(items.length / num_cols),
        difference = items.length - (min_items_per_col * num_cols);
      for (var i = 0; i < num_cols; i++) {
        items_per_col[i] = i < difference ? min_items_per_col + 1 : min_items_per_col;
      }
      for (var i = 0; i < num_cols; i++) {
        var subClass = 'list-' + i;
        //   subClass = i === (num_cols-1) ? subClass + ' last' : subClass;
        // console.log(subClass);
        $(this).append($('<div ></div>').addClass(listClass + ' ' + subClass));
        for (var j = 0; j < items_per_col[i]; j++) {
          var pointer = 0;
          for (var k = 0; k < i; k++) {
            pointer += items_per_col[k];
          }
          $(this).find('.' + subClass).last().append(items[j + pointer]);
        }
      }
    });
    list.addClass('col-' + num_cols);
  };

  Drupal.siSearch.splitContent = function (items, num_cols) {
    listClass = 'sub-list';

    var items_per_col = new Array(),
      min_items_per_col = Math.floor(items.length / num_cols),
      difference = items.length - (min_items_per_col * num_cols),
      lastItem = min_items_per_col * num_cols;
    $out = '';
    for (var i = 0; i < num_cols; i++) {
      items_per_col[i] = i < difference ? min_items_per_col + 1 : min_items_per_col;
    }

    $(items).each(function (index) {
      var $this = $(this);
      console.log(index);
      if (index === 0 || index === min_items_per_col) {
        console.log($this);
        $this.before('<div>');
      }
      if (index === min_items_per_col - 1 || index === lastItem - 1) {
        $this.after('</div>')
      }
    });
    //  for (var i = 0; i < num_cols; i++) {
    // //   var subClass = 'list-' + i;
    // //   //   subClass = i === (num_cols-1) ? subClass + ' last' : subClass;
    // //   // console.log(subClass);
    // //   $(this).append($('<div ></div>').addClass(listClass +' ' + subClass));
    //    for (var j = 0; j < items_per_col[i]; j++) {
    // //     var pointer = 0;
    // //     for (var k = 0; k < i; k++) {
    // //       pointer += items_per_col[k];
    // //     }
    // //     $(this).find('.' + subClass).last().append(items[j + pointer]);
    //    }
    //  }
  };

  Drupal.siSearch.queryURL = function (url) {
    var parser = document.createElement('a'),
      newQuery = [],
      values = {};

    parser.href = url;

    var query = parser.search.substring(1),
      params = query.split("&");

    for (var i = 0; i < params.length; i++) {
      var pair = params[i].split("=");
      if (pair[0] === 'page') {
        var page = decodeURI(pair[1]);
        page = parseInt(page);
        newPage = page + 1;
        newQuery[i] = 'page=' + newPage;
      }
      else {
        newQuery[i] = pair[0] + '=' + pair[1];
      }

    }
    var query = newQuery.join('&'),
      newUrl = url.split('?');
    newUrl = newUrl[0] + '?' + query;
    values.url = newUrl;
    values.page = newPage;
    return newUrl;
  }


  Drupal.siSearch.pager = function (masonry) {
    var nextSelector = $('.search-results-container .pager__item--next a'),
      lastSelector = $('.search-results-container .pager__item--last a').attr('href'),
      lastPage = false;
    if (nextSelector.length && hasRun === false) {
      nextSelector.text('Show More');

      nextSelector.click(function (e) {
        e.preventDefault();
        e.stopPropagation();
        var url = $(this).attr('href'),
          newSelector = $(this),
          id = $(this).parents('.search-results-container').attr('id'),
          Container = $('#' + id + ' .search-results'),
          item = '#' + id + ' .search-results li';
        if ($('#placeholder .loading').length === 0) {
          $('.search-results-container #placeholder').append('<div class="loading"></div>');
        }
        if (url === lastSelector) {
          lastPage = true;
        }
        //console.log(lastPage);
       // console.log(url);
        $.ajax({
          // type:"POST",
          url: url,
          success: function (data) {
            var $newElements = $(item, data),
              newUrl = Drupal.siSearch.queryURL(url);
            newSelector.attr('href', newUrl);

            $('.loading').remove();
            // console.log($newElements);
            Container.append($newElements);
            $newElements.imagesLoaded(function () {
              // Drupal.siSearch.checkImage($newElements);

              if (masonry === true) {
                Container.masonry('appended', $newElements);
              }
              Drupal.attachBehaviors(Container);
            })
              .progress(function (instance, image) {
                var result = image.isLoaded ? 'loaded' : 'broken',
                  imgSrc = image.img.src, imgHeight = $(image.img).height(),
                  parentH = $(image.img).parents('figure').height();

                if ($('.exhbition-search').length && parentH > imgHeight) {
                  $(image.img).addClass('landscape');
                  if ($(window).width() > 499) {
                    var $left = (imgHeight - parentH) / 2;
                    $(image.img).css('left', $left + 'px')
                  }
                }
                // if(result == 'broken') {
                //   $(image.img).addClass('hide').parents('.node--teaser').removeClass('has-media')
                // }
              });
          }
        });
        if (lastPage === true) {
          nextSelector.hide();
        }
      });
      hasRun = true;
    }
  }

  Drupal.behaviors.siSearch = {
    attach: function (context, settings) {

      siSearch = {
        setLayout: function () {
          var viewport = ($(window).width());
          // if(viewport >= 720) {
          //   // $('.float-list ul > li', context).matchHeight();
          //   // $('.paragraphs-item-three-column-grid .l-container .paragraphs-items > .paragraphs-item-video', context).matchHeight();
          //
          // }
          if ($('.masonry-grid', context).length) {
            var $grid = $('.masonry-grid', context);
            if (viewport > 500) {
              $grid.once('masonry', function () {
                //Masonry + ImagesLoaded
                $grid.imagesLoaded(function () {
                  $grid.masonry({
                    // selector for entry content
                    itemSelector: '.grid-item',
                    columnWidth: '.grid-item',
                    percentPosition: true
                  });
                })
                  .progress(function (instance, image) {
                    var result = image.isLoaded ? 'loaded' : 'broken';
                        imgHeight = $(image.img).height(),
                        imgWidth = $(image.img).width(),
                        parentH = $(image.img).parents('figure').height();
                    //imgHeight = $(image.img).height();
                    // console.log(imgHeight);
                    //image.img.attr('height', imgHeight);

                    if (result == 'broken') {
                      //$('img[src="' + imgSrc + '"]' ).addClass('hide');
                      // $(image.img).addClass('hide').parents('.node--teaser').removeClass('has-media')
                    }



                          var result = image.isLoaded ? 'loaded' : 'broken',
                            imgHeight = $(image.img).height(),
                            imgWidth = $(image.img).width(),
                            parentH = $(image.img).parents('figure').height();
                          // console.log(parentH);
                          // console.log(imgHeight);
                          if($(image.img).hasClass('exhibit-image') && parentH > imgHeight){

                            $(image.img).addClass('landscape');
                            if ($(window).width() > 499) {
                              var $left = (imgHeight - parentH) / 2;
                              $(image.img).css('left', $left + 'px')
                            }
                          }
                          $(image.img).attr('height', imgHeight).attr('width', imgWidth);
                          if(result == 'broken') {
                            $(image.img).addClass('hide').parents('.node--teaser').removeClass('has-media');
                          }



                  });
                // .progress( function( instance, image ) {
                //   var result = image.isLoaded ? 'loaded' : 'broken',
                //     imgSrc =image.img.src;
                //   if(result == 'broken') {
                //     $('img[src="' + imgSrc + '"]' ).addClass('hide');
                //   }
                // });
                Drupal.siSearch.pager(true);
              });

            }
            else {
              Drupal.siSearch.pager(false);
            }
          }
          else if ($('.search-results-container', context).length) {
            Drupal.siSearch.pager(false);
          }
        },
        init: function () {
          $('.l-content-wrapper img',context).each(function () {
            $(this).once('inspectImage', function () {
              $(this).imagesLoaded().progress(function (instance, image) {
                var result = image.isLoaded ? 'loaded' : 'broken',
                  imgHeight = $(image.img).height(),
                  imgWidth = $(image.img).width(),
                  parentH = $(image.img).parents('figure').height();
                //console.log(result);
                // console.log(imgHeight);
                if($(image.img).hasClass('exhibit-image') && parentH > imgHeight){

                  $(image.img).addClass('landscape');
                  if ($(window).width() > 499) {
                    var $left = (imgHeight - parentH) / 2;
                    $(image.img).css('left', $left + 'px')
                  }
                }
                $(image.img).attr('height', imgHeight).attr('width', imgWidth);
                // if(result == 'broken') {
                //   $(image.img).addClass('hide').parents('.node--teaser').removeClass('has-media');
                // }
              })
            });
          });
          if ($('.search-wrapper', context).length) {
            $('.filter-title a', context).click(function(e) {
              e.preventDefault();
              e.stopPropagation();
              $(this).parents('.search-wrapper').toggleClass('expanded');
            });
          }
          this.setLayout();
        }

      };

      siSearch.init();


      // Generic function that runs on window resize.
      function resizeStuff() {
        siSearch.setLayout();
      }

      // Runs function once on window resize.
      var TO = false;
      $(window).resize(function () {
        if (TO !== false) {
          clearTimeout(TO);
        }

        // 200 is time in miliseconds.
        TO = setTimeout(resizeStuff, 100);
      }).resize();

    }
  };


})(jQuery);