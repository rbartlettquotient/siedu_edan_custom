(function ($) {
    $(document).bind('cbox_complete', function () {
        Drupal.attachBehaviors('#cboxLoadedContent');
					var href = $.colorbox.element().attr("href"),
						url = href.split("?")[0];


					if (href) {
						//_gaq.push(["_trackPageview", href]);
						//pageTracker._trackPageview(href);
						console.log(url);
						ga('send','pageview', url);
					}

								// var elem = $.colorbox.element();
								// var tag = $(elem).attr('data-cb-tag');
								// if (typeof tag != 'undefined' && tag != false) {
										// 	var href = document.URL;
									//
									 //    		if (href.indexOf('#') != -1) {
									 //    			if (href.indexOf('?') != -1 && href.indexOf('#') > href.indexOf('?')) {
									 //        				href = href.replace('#', '&');
									 //        			} else {
									 //        				href = href.replace('#', '?');
									 //        			}
									 //    		}
									//
									 //    		if (href.indexOf('?') != -1) {
									 //    			if ((href.indexOf('?') +  1) < href.length && href.substr(href.length - 1, 1) != '&') {
									 //        				href = href  + '&';
									 //        			}
									 //    		} else {
									 //    			href = href + '?';
									 //    		}
									//
									 //    		href = href  + "tag=" + tag;
										// 	if (window._gat && window._gat._getTracker) {
									 //    			_gaq.push(["_trackPageview", href]);
									 //    		}
										// }
		});


})(jQuery);