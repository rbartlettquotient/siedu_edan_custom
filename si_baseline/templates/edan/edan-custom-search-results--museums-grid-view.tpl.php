
<?php
  if(module_exists('devel') && isset($_GET['dpm']) && user_access('access devel information')){
    dpm($variables);
  }

  elseif (isset($_GET['dump'])) {
    var_export($variables);
  }
?>

  <div class="l-container search-results grid-wrapper equal-col">
    <ul class="search-results<?php print $results_class; ?> reset-list content">
      <?php
      foreach ($docs as $doc):
        $class = implode(' ', $doc['row_attributes']['class']);
        ?>


      <li class="col-sm-6 col-md-4 col spacing-bottom" id="<?php print $doc['row_attributes']['id'] ?>">
        <div class="node--teaser node--teaser-long">
          <div class="inner">
            <?php if($doc['img_uri']): ?>
                <div class="b-media-wrapper field--type-image">
                  <a href="<?php print $doc['local_path']; ?>">
                    <img src="<?php print $doc['img_uri']; ?>" />
                  </a>
                </div>
            <?php endif; ?>

            <div class="b-text-wrapper">
              <h3 class="title"><a href="<?php echo $doc['local_path']; ?>"><?php print isset($doc['content']['title_shortname']) ? $doc['content']['title_shortname'] : $doc['title'];?></a></h3>
              <?php if($doc['type'] == 'location'): ?>
                <?php if($doc['content']['address']['content']) : ?>
                  <p class="location">
                    <?php print $doc['content']['address']['content'];?>
                    <?php if(isset($doc['content']['geolocation']['extended']['url'])) : ?>
                        <a href="<?php print $doc['content']['geolocation']['extended']['url'];?>" target="_blank" class="map-link block-display">
                          <?php print $doc['content']['geolocation']['extended']['url_text'] ? $doc['content']['geolocation']['extended']['url_text'] : '' ?>
                          <span class="fa fa-map-marker" aria-hidden="true"></span>
                        </a>
                    <?php endif; ?>
                  </p>
                <?php endif; ?>
                <?php if(isset($doc['content']['hours'])) : ?>
                  <p><?php echo $doc['content']['hours'];?></p>
                <?php endif; ?>
                <div><a href="<?php print $doc['local_path']; ?>" class="btn-text"><?php print t('Learn More'); ?></a></div>
              <?php endif; ?>
            </div>

          </div>
        </div>
      </li>

      <?php endforeach; ?>

    </ul>
  </div>

