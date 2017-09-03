<?php   if(module_exists('devel') && isset($_GET['dpm']) && user_access('access devel information')){
  dpm($variables);
}

elseif (isset($_GET['dump'])) {
  var_export($variables);
} ?>
<div class="l-container edan-search clearfix">
 <!-- 
   <?php if ($facets): ?>
  <div class="edan-search-facets">
    <?php echo $facets; ?>
  </div>
  <?php endif; ?>
-->
  <?php if ($tabs): ?>
  <div class="edan-search-tabs">
    <?php print($tabs); ?>
  </div>
  <?php endif; ?>

  <?php echo $pager; ?>


  <div id="search-<?php print $id; ?>" class="<?php print $container_class?>">
    <ul class="search-results<?php print $results_class; ?> reset-list">
      <?php foreach ($docs as $doc): ?>

        <li class="spacing-bottom" id="<?php print $doc['row_attributes']['id'] ?>">
          <div class="node--teaser node--teaser-featured<?php print isset($doc['img_uri']) ? ' has-media' : ''?>">
            <div class="inner">
              <?php
                if(module_exists('devel') && isset($_GET['dpm']) && user_access('access devel information')):
                  dpm($doc);

                elseif (isset($_GET['dump'])): ?>
                  <h3 class="title"><?php print $doc['#title']; ?></h3>

                  '<pre>' <?php print var_export($doc, TRUE); ?> '</pre>'

                <?php else:?>
                  <?php if ($doc['img_uri']): ?>

                    <div class="b-media-wrapper field--type-image">
                      <?php if(isset($doc['#title_link']) && !empty($doc['#title_link'])):
                        $url = url($doc['#title_link']['path'], array('query' => $doc['#title_link']['query'], 'fragment' => $doc['#title_link']['fragment']));
                        ?>

                        <a href="<?php print $url;?>" title="Thumbnail image for <?php print $doc['#title_plain']; ?>">
                          <img src="<?php echo $doc['img_uri']; ?> " alt="<?php print $doc['#title_plain']; ?>" />
                        </a>
                      <?php else: ?>
                        <img src="<?php echo $doc['img_uri']; ?> " alt="<?php print $doc['#title_plain']; ?>" />
                      <?php endif; ?>
                    </div>
                  <?php endif; ?>
                  <div class="b-text-wrapper">
                    <h3 class="title"><?php echo $doc['#title']; ?></h3>
                    <div class="si-unit-url"><a href="<?php print $doc['content']['record_link'];?>"><?php print $doc['content']['record_link'];?></a></div>
                    <div class="teaser"><?php print $doc['teaser'] ?></div>
                  </div>
                <?php endif; // End If ?>
              </div>
          </div>
        </li>
      <?php endforeach; ?>

    </ul>


  <?php if ($facets): ?>
    <?php
    // $facets contains the formatted facet content
    // $facets_raw is an array of facet data, which can be used for custom formatting facets
    // $active_facets_raw is an array of the currently active/selected facets
    ?>
    <div class="edan-search-facets">
      <?php echo $facets; ?>
    </div>
  <?php endif; ?>

  <?php echo $pager; ?>
    </div>
</div>