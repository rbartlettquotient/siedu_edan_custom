<?php dpm($variables); ?>

<div class="edan-search clearfix">
  <div class="l-container edan-search-results grid-wrapper equal-col">
    <ul class="search-results<?php print $results_class; ?> content">
      <?php
      foreach ($docs as $doc):
        $class = implode(' ', $doc['row_attributes']['class']);
        ?>
      <?php
        if(module_exists('devel') && isset($_GET['dpm']) && user_access('access devel information')):
        dpm($doc);

      elseif (isset($_GET['dump'])):
        echo '<pre>' . var_export($doc, TRUE) . '</pre>';
      else: ?>

      <li class="col-sm-6 col-md-4 col spacing-bottom" id="<?php print $doc['row_attributes']['id'] ?>">
        <div class="node--teaser node--teaser-long">
          <div class="inner">
            <div class="b-media-wrapper field--type-image">
              <a href="<?php echo $doc['local_path']; ?>">
                <img src="<?php print $doc['img_uri']; ?>" />
              </a>
            </div>
            <div class="b-text-wrapper">
              <h3 class="title"><?php print $doc['#title'];?></h3>
              <?php if($doc['content']['address']['content']) : ?>
                <p class="location">
                  <?php print $doc['content']['address']['content'];?>
                  <?php if(isset($doc['content']['geolocation']['extended']['url'])) : ?>
                      <a href="<?php echo $doc['content']['geolocation']['extended']['url'];?>" target="_blank" class="map-link">
                        <span class="fa fa-map-o" aria-hidden="true"></span>
                        <?php print $doc['content']['geolocation']['extended']['url_text'] ? $doc['content']['geolocation']['extended']['url_text'] : '' ?>
                      </a>
                  <?php endif; ?>
                </p>
              <?php endif; ?>
              <?php if(isset($doc['content']['hours'])) : ?>
                <p><?php echo $doc['content']['hours'];?></p>
              <?php endif; ?>



              <div><a href="<?php echo $doc['local_path']; ?>" class="btn blue"><?php print t('Learn More'); ?></a></div>
            </div>
          </div>
        </div>
      </li>
      <?php endif; ?>
      <?php endforeach; ?>

    </ul>
  </div>
</div>
